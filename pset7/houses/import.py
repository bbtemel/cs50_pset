from sys import argv,exit
from cs50 import SQL
import csv

if len(argv) !=2:
    print("You entered the wrong number of arguments")
    exit(1)

db = SQL("sqlite:///students.db")

with open(argv[1], "r") as char:
    reader = csv.DictReader(char)

    for row in reader:
        fulname = row["name"].split(" ")
        if len(fulname) == 2:
                 db.execute("INSERT INTO students (first,middle,last,house, birth) VALUES (?, ?, ?, ?, ?)",fulname[0], "NULL", fulname[1], row["house"], int(row["birth"]))
        elif len(fulname) == 3:
            db.execute("INSERT INTO students (first,middle,last,house, birth) VALUES (?, ?, ?, ?, ?)",fulname[0], fulname[1], fulname[2], row["house"], int(row["birth"]))
