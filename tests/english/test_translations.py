import requests
import json
import random
import sys
import os
import pytest

from data_generator import Fake
from client import Client

API_URL = "http://localhost:5050/api/"
PATH_TO_ADMIN_TRANSLATIONS = "english/admin/translations"

class TestAdminTranslations:

    def setup_method(self, method):
        Client.clear_translations()

    @pytest.fixture()
    def translation_data(self, request):
        return Client.get_random_translation_data()

    @pytest.fixture()
    def registered_headers(self, request):
        user = Fake.user()
        Client.register_user(user)
        response = Client.login_user(user)[1]

        return { "Authorization": response["Body"]["SessionToken"] }

    @pytest.fixture()
    def admin_headers(self, request):
        return Client.admin_headers()

    def test_create_access_denied_for_not_registered_user(self):
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {})

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_access_denied_for_registered_user(self, registered_headers):
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {}, registered_headers)
        
        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_validation_error_required(self, admin_headers):
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {}, admin_headers)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("ValueTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

    def test_create_with_incorrect_frequency(self, admin_headers, translation_data):
        translation_data["Frequency"] = "+"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = "gfsfg"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = "-03535"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = ""
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

        translation_data["Frequency"] = "0.2525"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = "9999999999"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeLessThan"

        translation_data["Frequency"] = "945834863496394867389467398467398674999999999"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeLessThan"

    def test_create_with_correct_frequency(self, admin_headers, translation_data):
        translation_data["Frequency"] = "125"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert status
        assert response.get("Status") == "Ok"

    def test_create_with_zero_frequency(self, admin_headers, translation_data):
        translation_data["Frequency"] = "0"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert status
        assert response.get("Status") == "Ok"

    def test_create_validation_error_same(self, admin_headers, translation_data):
        Client.create_translation(translation_data)
        status, response = Client.create_translation(translation_data)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "AlreadyExists"

    def test_create_ok(self, admin_headers, translation_data):
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)

        assert status
        assert response.get("Status") == "Ok"

    def test_get_access_denied_for_not_registered_user(self):
        status, response = Client.get_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {})

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_access_denied_for_registered(self, registered_headers):
        status, response = Client.get_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {}, registered_headers)

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_empty(self, admin_headers):
        status, response = Client.get_translations()
        
        assert status
        assert int(response["Body"]["TranslationsCount"]) == 0
        assert not response["Body"]["Translations"]

    def test_get_some(self):
        translations_count = 10
        for i in range(translations_count):
            Client.create_translation(Client.get_random_translation_data())

        status, response = Client.get_translations()
        assert status
        assert response["Body"]["TranslationsCount"] == translations_count
        assert len(response["Body"]["Translations"]) == translations_count

    def test_get_with_pagination(self):
        translations_count = 10
        for i in range(translations_count):
            Client.create_translation(Client.get_random_translation_data())

        status, response = Client.get_translations({"PageSize": 5, "Page": 0})
        assert status
        assert response["Body"]["TranslationsCount"] == translations_count
        assert len(response["Body"]["Translations"]) == 5

        status, response = Client.get_translations({"PageSize": 8, "Page": 1})
        assert status
        assert response["Body"]["TranslationsCount"] == translations_count
        assert len(response["Body"]["Translations"]) == 2

        status, response = Client.get_translations({"PageSize": 2, "Page": 9})
        assert status
        assert response["Body"]["TranslationsCount"] == translations_count
        assert not response["Body"]["Translations"]
