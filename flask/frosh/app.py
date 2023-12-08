from flask import Flask,render_template,request,session,redirect
from flask_session import Session

site  = Flask(__name__)

SPORTS = ['pen', 'finger', 'd']

site.config["SESSION_PERMANENT"] = False
site.config["SESSION_TYPE"] = "filesystem"
Session(site)

@site.route("/")
def index():
    if not session.get("name") :
        return redirect("/login")
    return render_template("index.html",sports =  SPORTS, naam = session["name"])


@site.route("/login",methods = ["GET" ,"POST"])
def login():
    if request.method == "POST":
        session["name"] = request.form.get("name")
        return redirect("/")
    return render_template("login.html")


@site.route("/register", methods =["POST"])
def register():
    if request.form.get("sport") not in SPORTS:
        return render_template("failure.html")
    else:
        return render_template("success.html", name=request.form.get("name") )

