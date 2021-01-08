import requests
import json
import random
from data_generator import Fake

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"
PATH_TO_LOGOUT = "english/logout"

PATH_TO_ADMIN_TRANSLATIONS = "english/admin/translations"
PATH_TO_ADMIN_WORD_CATEGORIES = "english/admin/word_categories"
PATH_TO_ADMIN_USERS = "english/admin/users"

class Client:

    def __init__(self, api_url):
        self.api_url = api_url

    def get_request(self, path, data, headers = {}):
        url_with_params = self.api_url + path + "?"
        for key in data:
            url_with_params += key + "=" + str(data[key]) + "&"
        r = requests.get(url_with_params, headers=headers)
        res = r.json()
        res["status_code"] = r.status_code
        return res

    def post_request(self, path, data, headers = {}):
        r = requests.post(self.api_url + path, data=json.dumps(data), headers=headers)
        res = r.json()
        res["status_code"] = r.status_code
        return res

    def put_request(self, path, data, headers = {}):
        r = requests.put(self.api_url + path, data=json.dumps(data), headers=headers)
        res = r.json()
        res["status_code"] = r.status_code
        return res

    def delete_request(self, path, data, headers = {}):
        r = requests.delete(self.api_url + path, data=json.dumps(data), headers=headers)
        res = r.json()
        res["status_code"] = r.status_code
        return res

    # common methods
    def registered_headers(self):
        user = Fake.user()
        self.register_user(user)
        response = self.login_user(user)
        return { "Authorization": response["Body"]["SessionToken"] }

    def admin_headers(self):
        response = self.login_user({"Email": "admin@admin.ru", "Password": "admin"})
        return { "Authorization": response["Body"]["SessionToken"] }

    # english users
    def register_user(self, user):
        return self.post_request(PATH_TO_REGISTER_USER, user)

    def login_user(self, user):
        return self.post_request(PATH_TO_LOGIN_USER, user)

    def logout(self, data):
        return self.delete_request(PATH_TO_LOGOUT, data)

    # english/admin/translations
    def get_translation_by_id(self, translation, headers = {}):
        return self.get_request(PATH_TO_ADMIN_TRANSLATIONS + "/" + translation["Id"], {}, headers)

    def get_translations(self, params = {}, headers = {}):
        return self.get_request(PATH_TO_ADMIN_TRANSLATIONS, params, headers)

    def delete_translation(self, translation, headers = {}):
        return self.delete_request(PATH_TO_ADMIN_TRANSLATIONS + "/" + translation["Id"], {}, headers)

    def create_translation(self, translation, headers = {}):
        return self.post_request(PATH_TO_ADMIN_TRANSLATIONS, translation, headers)

    def edit_translation(self, translation, headers = {}):
        return self.put_request(PATH_TO_ADMIN_TRANSLATIONS, translation, headers)

    def get_translations_for_autocomplete(self, name, headers = {}):
        return self.get_request(PATH_TO_ADMIN_TRANSLATIONS + "_for_autocomplete", { "Name": name }, headers)

    def get_translations_by_full_matching(self, translation, headers = {}):
        return self.get_request("english/admin/translation_by_full_matching", translation, headers)

    def clear_translations(self, headers = {}):
        response = self.get_request(PATH_TO_ADMIN_TRANSLATIONS, {}, headers)
        if response["Body"]["Records"]:
            for translation in response["Body"]["Records"]:
                self.delete_translation(translation, headers)

    # english/admin/word_categories
    def get_word_category_by_id(self, word_category, headers = {}):
        return self.get_request(PATH_TO_ADMIN_WORD_CATEGORIES + "/" + word_category["Id"], {}, headers)

    def get_word_categories(self, params = {}, headers = {}):
        return self.get_request(PATH_TO_ADMIN_WORD_CATEGORIES, params, headers)

    def delete_word_category(self, word_category, headers = {}):
        return self.delete_request(PATH_TO_ADMIN_WORD_CATEGORIES + "/" + word_category["Id"], {}, headers)

    def create_word_category(self, word_category, headers = {}):
        return self.post_request(PATH_TO_ADMIN_WORD_CATEGORIES, word_category, headers)

    def edit_word_category(self, word_category, headers = {}):
        return self.put_request(PATH_TO_ADMIN_WORD_CATEGORIES, word_category, headers)

    def clear_word_categories(self, headers = {}):
        response = self.get_request(PATH_TO_ADMIN_WORD_CATEGORIES, {}, headers)
        if response["Body"]["Records"]:
            for word_category in response["Body"]["Records"]:
                self.delete_word_category(word_category, headers)

    # english/admin/users
    def get_user_by_id(self, user, headers = {}):
        return self.get_request(PATH_TO_ADMIN_USERS + "/" + user["Id"], {}, headers)

    def get_users(self, params = {}, headers = {}):
        return self.get_request(PATH_TO_ADMIN_USERS, params, headers)

    def delete_user(self, user, headers = {}):
        return self.delete_request(PATH_TO_ADMIN_USERS + "/" + user["Id"], {}, headers)

    def create_user(self, user, headers = {}):
        return self.post_request(PATH_TO_ADMIN_USERS, user, headers)

    def edit_user(self, user, headers = {}):
        return self.put_request(PATH_TO_ADMIN_USERS, user, headers)

    def clear_users(self, headers = {}):
        response = self.get_request(PATH_TO_ADMIN_USERS, {}, headers)
        if response["Body"]["Records"]:
            for user in response["Body"]["Records"]:
                if user["Email"] != "admin@admin.ru":
                    self.delete_user(user, headers)
