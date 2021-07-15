import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id ORDER BY stock ASC", user_id=session["user_id"])
    user = db.execute("SELECT * FROM users WHERE id = :id", id=session["user_id"])
    grand_total = 0.0

    for i in range(len(stocks)):
        stock = lookup(stocks[i]["stock"])
        stocks[i]["company"] = stock["name"]
        stocks[i]["cur_price"] = "%.2f"%(stock["price"])
        stocks[i]["cur_total"] = "%.2f"%(float(stock["price"]) * float(stocks[i]["quantity"]))
        stocks[i]["profit"] = "%.2f"%(float(stocks[i]["cur_total"]) - float(stocks[i]["total"]))
        grand_total += stocks[i]["total"]
        stocks[i]["total"] = "%.2f"%(stocks[i]["total"])

    grand_total += float(user[0]["cash"])

    return render_template("index.html", stocks=stocks, cash=usd(user[0]["cash"]), grand_total=usd(grand_total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if (not request.form.get("symbol")) or (not request.form.get("quantity")) or (int(request.form.get("quantity")) < 1):
            return apology("please provide valid entries")

        stock = lookup(request.form.get("symbol").upper())
        if stock == None:
            return apology("Symbol you entered is invalid")
        cost = int(request.form.get("quantity")) * stock['price']

        cash = db.execute("SELECT cash FROM users WHERE id=:id",id = session["user_id"])
        if cost > cash[0]["cash"]:
            return apology("you do not have enough cash for this transaction")
        db.execute("UPDATE users SET cash=cash-:cost WHERE id=:id", cost=cost, id=session["user_id"]);
        add_transaction = db.execute("INSERT INTO transactions (user_id, stock, quantity, price, date, action) VALUES (:user_id, :stock, :quantity, :price, :date, :action)", user_id=session["user_id"], stock=stock["symbol"], quantity=int(request.form.get("quantity")), price=stock['price'], date=datetime.now().strftime("%Y-%m-%d %H:%M:%S"), action ="BUY")
        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND stock = :stock",user_id=session["user_id"], stock=stock["symbol"])

        # update with new price if already owned
        if len(stock_db) == 1:

            new_quantity = int(stock_db[0]["quantity"]) + int(request.form.get("quantity"))
            new_total = float(stock_db[0]["total"]) + cost
            new_pps = "%.2f"%(new_total / float(new_quantity))

            db.execute("UPDATE stocks SET quantity = :quantity, total = :total, pps = :pps WHERE user_id = :user_id AND stock = :stock", quantity=new_quantity, total=new_total, pps=new_pps, user_id=session["user_id"], stock=stock["symbol"])

        # else create a new entry in db
        else:

            db.execute("INSERT INTO stocks (user_id, stock, quantity, total, pps) VALUES (:user_id, :stock, :quantity, :total, :pps)",user_id=session["user_id"], stock=stock["symbol"], quantity=request.form.get("quantity"), total=cost, pps=stock["price"])

        return apology("Action Succesfull")
    else:
        return render_template("buy.html")



@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
     # retrieve history from db
    stocks = db.execute("SELECT * FROM transactions WHERE user_id = :user_id ORDER BY date DESC", user_id=session["user_id"])

    # calculate total price of transaction
    for i in range(len(stocks)):
        stocks[i]["total"] = "%.2f"%(float(stocks[i]["quantity"]) * float(stocks[i]["price"]))

    # render table
    return render_template("history.html", stocks=stocks)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure name of stock was submitted
        if not request.form.get("symbol"):
            return apology("must provide stock symbol")

        # pull quote from yahoo finance
        quote = lookup(request.form.get("symbol"))

        # check is valid stock name provided
        if quote == None:
            return apology("Stock symbol not valid, please try again")

        # stock name is valid
        else:
            return render_template("quoted.html", quote=quote, price=usd(quote["price"]))

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("quote.html")

@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("You must provide a username")
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("You must provide password and confirmation")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords are not matching")

        hash = generate_password_hash(request.form.get("password"))
        result = db.execute("INSERT INTO users (username, hash) VALUES (:username, :hash)", username=request.form.get("username"), hash = hash)
        if not result:
            return apology("Username already exist")
        session["user_id"] = result
        return redirect("/")

    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    stocks = db.execute("SELECT * FROM stocks WHERE user_id = :user_id", user_id=session["user_id"])

    # if user reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # ensure quantity was submited
        if not request.form.get("quantity") or int(request.form.get("quantity")) < 1:
            return render_template("sell.html", stocks=stocks)

        user_id = session["user_id"]
        symbol = request.form.get("symbol").upper()
        quantity = request.form.get("quantity")

        # retrieve stock from db
        stock_db = db.execute("SELECT * FROM stocks WHERE user_id = :user_id AND stock = :stock",user_id=user_id, stock=symbol)

        if stock_db:
            stock_db = stock_db[0]
        else:
            return render_template("sell.html", stocks=stocks)

        # retrieve user data from db
        user = db.execute("SELECT * FROM users WHERE id = :id", id=user_id)

        # ensure quantity to be sold is available
        if int(quantity) > stock_db["quantity"]:
            return apology("not enough shares")

        # lookup the stock to get current price
        stock = lookup(symbol)

        # calculate total price
        total_price = float(stock["price"]) * float(quantity)

        # modify number of shares owned or delete if < 1
        if int(quantity) == stock_db["quantity"]:
            db.execute("DELETE FROM stocks WHERE user_id = :user_id AND stock = :stock", user_id=user_id, stock=symbol)
        else:
            new_quantity = int(stock_db["quantity"]) - int(quantity)
            new_total = float(new_quantity) * float(stock_db["pps"])
            db.execute("UPDATE stocks SET quantity = :quantity, total = :total WHERE user_id = :user_id AND stock = :stock", quantity=new_quantity, total=new_total, user_id=user_id, stock=symbol)

        # modify available funds
        funds_available = float(user[0]["cash"]) + total_price
        db.execute("UPDATE users SET cash = :cash WHERE id = :id", cash=funds_available, id=user_id)

        # commit to history
        db.execute("INSERT INTO transactions (user_id, action, stock, quantity, price, date) VALUES (:user_id, :action, :stock, :quantity, :price, :date)", user_id=user_id, action="SELL", stock=symbol, quantity=quantity, price=stock["price"], date=datetime.now().strftime("%Y-%m-%d %H:%M:%S"))

        # send a success message
        return apology("Sell Successfull buy for more profit ;)")

    # else if user reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("sell.html", stocks=stocks)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
