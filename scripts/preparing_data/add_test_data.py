import requests
import json
import random

API_URL = "http://localhost:1234/api/"

def register_user(user):
    r = requests.post(API_URL + "english/users", data=json.dumps(user))
    if r.status_code == 200:
        result = r.json()
        if result["Status"] == "Ok":
            print("User with email " + user["Email"] + " is registered")
        else:
            print(result)
    else:
        print(r.status_code)

def login_user(user):
    r = requests.post(API_URL + "english/login", data=json.dumps({
        "Email": user["Email"],
        "Password": user["Password"]
    }))
    if r.status_code == 200:
        result = r.json()
        if result["Status"] == "Ok":
            print("User with email " + user["Email"] + " is login")
        else:
            print(result)
    else:
        print(r.status_code)    

def get_random_phone():
    result = "+7"
    for i in range(10):
        result += str(random.randint(0, 9))

    return result

def main():
    print("Task is started")
    users = []

    for i in range(100):
        users.append({
            "Email": "email" + str(i) + "@example.ru",
            "Name": "Username #" + str(i),
            "Phone": get_random_phone(),
            "Password": "123",
            "RepeatPassword": "123"
        })

    for user in users:
        register_user(user)

    for user in users:
        for i in range(0, random.randint(0, 4)):
            login_user(user)

main()
