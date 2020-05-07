import requests
import json
import random
from data_generator import Fake

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"
PATH_TO_LOGOUT = "english/logout"

PATH_TO_ADMIN_TRANSLATIONS = "english/admin/translations"

class Client:

    def __init__(self, api_url):
        self.api_url = api_url

    def get_request(self, url, data, headers = dict()):
        url_with_params = url + "?"
        for key in data:
            url_with_params += key + "=" + str(data[key]) + "&"
        r = requests.get(url_with_params, headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]

    def post_request(self, url, data, headers = dict()):
        r = requests.post(url, data=json.dumps(data), headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]

    def put_request(self, url, data, headers = dict()):
        r = requests.put(url, data=json.dumps(data), headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]

    def delete_request(self, url, data, headers = dict()):
        r = requests.delete(url, data=json.dumps(data), headers=headers)
        if r.status_code == 200:
            return [True, r.json()]
        else:
            return [False, r.status_code]

    def registered_headers(self):
        user = Fake.user()
        self.register_user(user)
        response = self.login_user(user)[1]

        return { "Authorization": response["Body"]["SessionToken"] }

    def admin_headers(self):
        response = self.login_user({"Email": "admin@admin.ru", "Password": "admin"})[1]
        return { "Authorization": response["Body"]["SessionToken"] }

    def register_user(self, user):
        return self.post_request(
            self.api_url + PATH_TO_REGISTER_USER,
            user
        )

    def login_user(self, user):
        return self.post_request(
            self.api_url + PATH_TO_LOGIN_USER,
            user
        )

    def login_as_admin(self):
        res = self.post_request(
            self.api_url + PATH_TO_LOGIN_USER,
            {
                "Email": "admin@admin.ru",
                "Password": "admin"
            }
        )

        return res[1]["Body"]["SessionToken"]

    def logout(self, token):
        return self.delete_request(self.api_url + PATH_TO_LOGOUT, {})

    def clear_translations(self):
        _, response = self.get_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS, {}, self.admin_headers())
        if response["Body"]["Translations"]:
            for translation in response["Body"]["Translations"]:
                self.delete_translation(translation)

    def get_translation_by_id(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.get_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS + "/" + translation["Id"], {}, headers)

    def get_translations(self, params = {}, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.get_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS, params, headers)

    def delete_translation(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.delete_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS + "/" + translation["Id"], {}, headers)

    def create_translation(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.post_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS, translation, headers)

    def edit_translation(self, translation, headers = None):
        if headers == None:
            headers = self.admin_headers()
        return self.put_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS, translation, headers)

    def clear_translations(self):
        _, response = self.get_request(self.api_url + PATH_TO_ADMIN_TRANSLATIONS, {}, self.admin_headers())
        if response["Body"]["Records"]:
            for translation in response["Body"]["Records"]:
                self.delete_translation(translation)
