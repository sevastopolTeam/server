import requests
import json
import random
import sys
import os
import pytest

from data_generator import Fake
from client import Client

API_URL = "http://localhost:1234/api/"
PATH_TO_ADMIN_TRANSLATIONS = "english/admin/translations"

@pytest.fixture()
def registered_headers(request):
    user = Fake.user()
    Client.register_user(user)
    response = Client.login_user(user)[1]

    return { "Authorization": response["Body"]["SessionToken"] }

@pytest.fixture()
def translation_data(request):
    return {
        "ValueFrom": Fake.string(5),
        "ValueTo": Fake.string(5),
        "LanguageFrom": "русский",
        "LanguageTo": "english",

    }

class TestTranslations:

    def test_access_denied_to_translations_not_registered_user(self):
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {})
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_access_denied_to_translations(self, registered_headers):
        status, response = Client.post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {}, admin_headers)
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_access_denied_create_translation(self, registered_headers):

