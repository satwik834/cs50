import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
@login_required
def index():
    id = session["user_id"]
    if request.method == "POST":
        db.execute("UPDATE users SET cash = ? WHERE id = ?", 10000, id)
        db.execute("DELETE FROM shares WHERE id = ?", id)

    """Show portfolio of stocks"""
    info = db.execute("SELECT * FROM shares WHERE id = ?", id)
    cash = db.execute("SELECT cash FROM users where id = ? ", id)[0]["cash"]
    total = cash
    for share in info:
        current_price = lookup(share["symbol"])["price"]
        share["current_price"] = current_price
        total += float(share["price"]) * float(share["quantity"])

    return render_template("index.html", info=info, cash=cash, total=round(total))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        userid = session["user_id"]
        symbol = request.form.get("symbol").upper()
        quantity = request.form.get("shares")

        cash = db.execute("SELECT cash FROM users WHERE id  = ? ", userid)[0]["cash"]

        if len(symbol) == 0:
            return apology("must enter symbol of stock")

        if quantity == None:
            return apology("invalid quantity")
        try:
            quantity = int(quantity)
        except ValueError:
            return apology("invalid quantity")

        if int(quantity) <= 0:
            return apology("invalid quantity")

        if lookup(symbol) == None:
            return apology("stock does not fucking exist")

        price = lookup(symbol)["price"]
        if price * float(quantity) > cash:
            return apology("you are poor")

        shares = db.execute("SELECT * FROM shares WHERE id = ?", userid)
        for share in shares:
            if share["symbol"] == symbol:
                final_quantity = int(share["quantity"]) + int(quantity)
                total = share["total"] + price * float(quantity)
                db.execute(
                    "UPDATE shares SET quantity = ? WHERE symbol  = ? AND id = ?",
                    final_quantity,
                    symbol,
                    userid,
                )
                db.execute(
                    "UPDATE shares SET total = ? WHERE symbol = ? AND id = ?",
                    total,
                    symbol,
                    userid,
                )
                final_cash = cash - price * float(quantity)
                db.execute("UPDATE users SET cash = ? WHERE id = ?", final_cash, userid)
                return redirect("/")

        db.execute(
            "INSERT INTO shares (symbol,price,quantity,total,id) values(?,?,?,?,?)",
            symbol,
            price,
            quantity,
            round(price * float(quantity), 2),
            userid,
        )
        final_cash = cash - price * float(quantity)
        db.execute("UPDATE users SET cash = ? WHERE id = ?", final_cash, userid)
        return redirect("/")

    if request.method == "GET":
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


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
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
    if request.method == "GET":
        return render_template("quote.html")

    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol == "":
            return apology("must enter stock symbol")
        if lookup(symbol) == None:
            return apology("invalid symbol")
        price = lookup(symbol)["price"]
        return render_template("quoted.html", price=price, name=symbol)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        password_hash = generate_password_hash(request.form.get("password"))
        users = db.execute("SELECT username FROM users")
        if username == "":
            return apology("MUST provide username")
        if password == "" or confirmation == "" or password != confirmation:
            return apology("password is blank or they do not match")
        for user in users:
            if user["username"] == username:
                return apology(
                    "username already exists try again with a different username"
                )

        db.execute(
            "INSERT INTO users (username,hash) values(?,?)", username, password_hash
        )
        return redirect("/login")

    if request.method == "GET":
        users = db.execute("SELECT username FROM users")
        return render_template(
            "register.html",
        )


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    id = session["user_id"]
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        quantity = int(request.form.get("shares"))
        price = lookup(symbol)["price"]
        id = session["user_id"]
        if len(symbol) == 0:
            return apology("must enter symbol of stock")

        if quantity == None:
            return apology("invalid quantity")
        try:
            quantity = int(quantity)
        except ValueError:
            return apology("invalid quantity")

        shares = db.execute("SELECT * FROM shares WHERE id = ?", id)
        cash = db.execute("SELECT cash FROM users WHERE id  = ?", id)[0]["cash"]
        owns_stock = False
        can_sell = False

        for share in shares:
            if share["symbol"] == symbol:
                owns_stock = True
                share_quantity = int(share["quantity"])
                if share_quantity >= int(quantity):
                    can_sell = True
                    share_value = share["total"]
                    db.execute(
                        "UPDATE shares SET quantity  = ? WHERE id = ? AND symbol = ?",
                        share_quantity - quantity,
                        id,
                        symbol,
                    )
                    db.execute(
                        "UPDATE shares SET total  = ? WHERE id = ? AND symbol = ?",
                        share_value - price * quantity,
                        id,
                        symbol,
                    )
                    db.execute(
                        "UPDATE users SET cash = ? WHERE id = ?",
                        cash + price * quantity,
                        id,
                    )

                    if share_quantity - quantity == 0:
                        db.execute(
                            "DELETE FROM shares WHERE id = ? AND symbol = ?", id, symbol
                        )

                    return redirect("/")

        if not can_sell:
            return apology("invalid quantity")

    if request.method == "GET":
        id = session["user_id"]
        shares = db.execute("SELECT * FROM shares WHERE id = ?", id)
        return render_template("sell.html", shares=shares)
