import requests
import json
import random

API_URL = "http://localhost:1234/api/"

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"

def post_request(url, data):
    r = requests.post(url, data=json.dumps(data))
    if r.status_code == 200:
        return [True, r.json()]
    else:
        return [False, r.status_code]

def filter_dict(input, keys):
    return { key: input.get(key) for key in keys }

def register_user(user):
    return post_request(
        API_URL + PATH_TO_REGISTER_USER,
        user
    )

def login_user(user):
    return post_request(
        API_URL + PATH_TO_LOGIN_USER,
        user
    )

def login_as_admin():
    res = post_request(
        API_URL + PATH_TO_LOGIN_USER,
        {
            "Email": "buriksurik@mail.ru",
            "Password": "123"
        }
    )

    return res[1]["Body"]["SessionToken"]
