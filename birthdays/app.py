import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response



@app.route("/", methods=["GET", "POST"])
def index():
    people = db.execute("SELECT * FROM birthdays")
    if request.method == "POST" :

        # TODO: Add the user's entry into the database
        name = request.form.get("name")
        day = request.form.get("day")
        month = request.form.get("month")
        if len(name) != 0 or len(day) != 0 or len(month) != 0  :
            db.execute("INSERT INTO birthdays (name,day,month) values(?,?,?)", name , day , month)

        return render_template("index.html", people = people)

    else:

        # TODO: Display the entries in the database on index.html

        return render_template("index.html",people  = people)


