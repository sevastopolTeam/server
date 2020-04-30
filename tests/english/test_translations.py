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

@pytest.fixture()
def registered_headers(request):
    user = Fake.user()
    Client.register_user(user)
    response = Client.login_user(user)[1]

    return { "Authorization": response["Body"]["SessionToken"] }

@pytest.fixture()
def admin_headers(request):
    response = Client.login_user({"Email": "admin@admin.ru", "Password": "admin"})[1]

    return { "Authorization": response["Body"]["SessionToken"] }


@pytest.fixture()
def translation_data(request):
    return {
        "ValueFrom": Fake.string(5),
        "ValueTo": Fake.string(5),
        "LanguageFrom": "russian",
        "LanguageTo": "english",
        "OriginUrl": "origin_url",
        "DownloadUrl": "download_url",
        "Frequency": 124
    }

class TestAdminTranslations:

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

    def test_create_with_frequency(self, admin_headers, translation_data):
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

        translation_data["Frequency"] = "125"
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        assert status
        assert response.get("Status") == "Ok"

    def test_create_validation_error_same(self, admin_headers, translation_data):
        Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, translation_data, admin_headers)

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
