import requests
import json
import random
from data_generator import Fake

API_URL = "http://localhost:5050/api/"

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"
PATH_TO_LOGOUT = "english/logout"

PATH_TO_ADMIN_TRANSLATIONS = "english/admin/translations"

class Client:

    @classmethod
    def get_request(self, url, data, headers = dict()):
        url_with_params = url + "?"
        for key in data:
            url_with_params += key + "=" + str(data[key]) + "&"
        r = requests.get(url_with_params, headers=headers)
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
    def put_request(self, url, data, headers = dict()):
        r = requests.put(url, data=json.dumps(data), headers=headers)
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
    def registered_headers(self):
        user = Fake.user()
        Client.register_user(user)
        response = Client.login_user(user)[1]

        return { "Authorization": response["Body"]["SessionToken"] }

    @classmethod
    def admin_headers(self):
        response = Client.login_user({"Email": "admin@admin.ru", "Password": "admin"})[1]
        return { "Authorization": response["Body"]["SessionToken"] }

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
                "Email": "admin@admin.ru",
                "Password": "admin"
            }
        )

        return res[1]["Body"]["SessionToken"]

    @classmethod
    def logout(self, token):
        return self.delete_request(API_URL + PATH_TO_LOGOUT, {})


    @classmethod
    def get_translation_by_id(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.get_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS + "/" + translation["Id"], {}, headers)

    @classmethod
    def get_translations(self, params = {}, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.get_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, params, headers)

    @classmethod
    def delete_translation(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.delete_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS + "/" + translation["Id"], {}, headers)

    @classmethod
    def create_translation(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation, headers)

    @classmethod
    def edit_translation(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.put_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation, headers)

    @classmethod
    def clear_translations(self):
        _, response = self.get_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {}, self.admin_headers())
        if response["Body"]["Records"]:
            for translation in response["Body"]["Records"]:
                self.delete_translation(translation)



