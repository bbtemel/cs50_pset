from sys import argv,exit
from cs50 import SQL
import csv

if len(argv) !=2:
    print("You entered the wrong number of arguments")
    exit(1)
s_house = argv[1]

db = SQL("sqlite:///students.db")

reader = db.execute("SELECT first,middle,last,birth FROM students WHERE house = ? ORDER BY last,first", s_house)

for row in reader:
    if row["middle"] != "NULL":
        print(row["first"], row ["middle"], row["last"],"," "born", row["birth"])
    else:
         print(row["first"], row["last"],"," "born", row["birth"])
