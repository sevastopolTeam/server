import requests
import json

API_URL = "http://localhost:1234/api/"

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"
PATH_TO_LOGOUT = "english/logout"


class Client:

    @classmethod
    def get_request(self, url, data, headers = dict()):
        r = requests.get(url, data=json.dumps(data), headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]

    @classmethod
    def post_request(self, url, data, headers = dict()):
        r = requests.post(url, data=json.dumps(data), headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]

    @classmethod
    def delete_request(self, url, data, headers = dict()):
        r = requests.delete(url, data=json.dumps(data), headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]


    @classmethod
    def filter_dict(self, input, keys):
        return { key: input.get(key) for key in keys }

    @classmethod
    def register_user(self, user):
        return self.post_request(
            API_URL + PATH_TO_REGISTER_USER,
            user
        )

    @classmethod
    def login_user(self, user):
        return self.post_request(
            API_URL + PATH_TO_LOGIN_USER,
            user
        )

    @classmethod
    def logout(self, user):
        return self.post_request(
            API_URL + PATH_TO_LOGIN_USER,
            user
        )

    @classmethod
    def login_as_admin(self):
        res = self.post_request(
            API_URL + PATH_TO_LOGIN_USER,
            {
                "Email": "buriksurik@mail.ru",
                "Password": "123"
            }
        )

        return res[1]["Body"]["SessionToken"]

    @classmethod
    def logout(self, token):
        return self.delete_request(API_URL + PATH_TO_LOGOUT, {})



