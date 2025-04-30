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


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # query holdings: group transactions by symbol
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])

    # for each row, look up live  price & compute value
    total_value = 0
    for row in rows:
        quote = lookup(row["symbol"])
        row["price"] = quote["price"]
        row["value"] = row["shares"] * row["price"]
        total_value += row["value"]

    # get user's cash
    cash_row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = cash_row[0]["cash"]

    # compute grand total
    grand_total = cash + total_value

    # render the portfolio template
    return render_template(
        "index.html",
        rows=rows,
        cash=cash,
        grand=grand_total
    )


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")

    # process the purchase
    symbol = request.form.get("symbol", "").strip().upper()
    shares_text = request.form.get("shares", "").strip()

    # validate symbol
    if not symbol:
        return apology("must provide symbol")

    # validate shares
    if not shares_text.isdigit():
        return apology("shares must be a integer")

    shares = int(shares_text)
    if shares < 1:
        return apology("shares must be a positive integer")

    # lookup current price
    quote = lookup(symbol)
    if quote is None:
        return apology("invalid symbol")
    price = quote["price"]
    total_cost = shares * price

    # check if the user has enough cash
    row = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    cash = row[0]["cash"]
    if total_cost > cash:
        return apology("can't afford")

    # deduct cash
    db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])

    # record the purchase
    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
               session["user_id"], symbol, shares, price)

    # let the user know and go back to portfolio
    flash("Bought!")
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # query all transactions for this user, newest first
    rows = db.execute("""
                      SELECT symbol, shares, price, timestamp
                      FROM transactions
                      WHERE user_id = ?
                      ORDER BY timestamp DESC
                      """, session["user_id"]
                      )
    # render history template with that list
    return render_template("history.html", rows=rows)


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
    if request.method == "POST":

        # Get the symbol the user typed
        symbol = request.form.get("symbol")

        # Check if user didn't type anything
        if not symbol:
            return apology("must provide symbol")

        # Look up the stock symbol
        stock = lookup(symbol)

        # Check if lookup failed
        if stock is None:
            return apology("invalid symbol")

        # If everything OK, show the user the price
        return render_template("quoted.html", stock=stock)
    else:

        # If GET(user just clicks Quote button), show the form
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    # Get users data for submitting it to server
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Make sure user enters every field and has matching passwords
        if not username or not password or not confirmation:
            return apology("missing fields")
        if password != confirmation:
            return apology("passwords must match")

        # Generate a hash for password to store it into server
        hash_pw = generate_password_hash(password)

        # Store users information to server for recognizing the same user
        # and make sure the username is not taken
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash_pw)
        except:
            return apology("username already taken")
        # Log the new user in
        rows = db.execute("SELECT id FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "GET":
        # which symbols does this user own?
        symbols = db.execute("SELECT symbol"
                             " FROM transactions"
                             " WHERE user_id = ?"
                             " GROUP BY symbol"
                             " HAVING SUM(shares) > 0", session["user_id"])
        render_template("sell.html", symbols=symbols)
        # grab from data
        return render_template("sell.html", symbols=symbols)
    symbol = request.form.get("symbol")
    shares_text = request.form.get("shares", "").strip()
    # validate shares input
    try:
        shares = int(shares_text)
        if shares < 1:
            return apology("must provide a positive integer")
    except ValueError:
        return apology("invalid share count")
    # check holding count
    row = db.execute(
        "SELECT COALESCE (SUM(shares), 0) AS owned FROM transactions WHERE user_id = ? AND symbol = ?", session["user_id"], symbol)
    owned = row[0]["owned"]
    if shares > owned:
        return apology("not enough shares to sell")
    # lookup current price
    quote = lookup(symbol)
    if quote is None:
        return apology("invalid symbol?")
    # compute proceeds
    proceeds = shares * quote["price"]
    # update db
    db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", proceeds, session["user_id"])
    # record transaction
    db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
               session["user_id"], symbol, -shares, quote["price"])
    flash("Sold!")
    return redirect("/")
