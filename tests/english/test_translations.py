import json
import random
import sys
import os
import pytest

from data_generator import Fake
from client import Client

class TestAdminTranslations:

    def setup_method(self, method):
        Client.clear_translations()

    @pytest.fixture()
    def translation_data(self, request):
        return Fake.translation()

    @pytest.fixture()
    def registered_headers(self, request):
        return Client.registered_headers()

    @pytest.fixture()
    def admin_headers(self, request):
        return Client.admin_headers()

    def test_create_access_denied_for_not_registered_user(self):
        status, response = Client.create_translation({}, {})

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_access_denied_for_registered_user(self, registered_headers):
        status, response = Client.create_translation({}, registered_headers)

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_validation_error_required(self):
        status, response = Client.create_translation({})

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("ValueTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

    def test_create_with_incorrect_frequency(self, translation_data):
        translation_data["Frequency"] = "+"
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = "gfsfg"
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = "-03535"
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = ""
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

        translation_data["Frequency"] = "0.2525"
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation_data["Frequency"] = "9999999999"
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeLessThan"

        translation_data["Frequency"] = "945834863496394867389467398467398674999999999"
        status, response = Client.create_translation(translation_data)
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeLessThan"

    def test_create_with_correct_frequency(self, translation_data):
        translation_data["Frequency"] = "125"
        status, response = Client.create_translation(translation_data)
        assert status
        assert response.get("Status") == "Ok"

        translation_id = response["Body"]["Id"]
        _, response = Client.get_translation_by_id({ "Id": translation_id })
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == translation_id

    def test_create_with_zero_frequency(self, translation_data):
        translation_data["Frequency"] = "0"
        status, response = Client.create_translation(translation_data)
        assert status
        assert response.get("Status") == "Ok"

        translation_id = response["Body"]["Id"]
        _, response = Client.get_translation_by_id({ "Id": translation_id })
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == translation_id

    def test_create_validation_error_same(self, translation_data):
        Client.create_translation(translation_data)
        status, response = Client.create_translation(translation_data)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "AlreadyExists"

    def test_create_ok(self, translation_data):
        status, response = Client.create_translation(translation_data)

        assert status
        assert response.get("Status") == "Ok"

    def test_get_access_denied_for_not_registered_user(self):
        status, response = Client.get_translations({}, {})

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_access_denied_for_registered(self, registered_headers):
        status, response = Client.get_translations({}, registered_headers)

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
            Client.create_translation(Fake.translation())

        status, response = Client.get_translations()
        assert status
        assert response["Body"]["TranslationsCount"] == translations_count
        assert len(response["Body"]["Translations"]) == translations_count

    def test_get_with_pagination(self):
        translations_count = 10
        for i in range(translations_count):
            Client.create_translation(Fake.translation())

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

    def test_delete_access_denied_for_unregistered(self):
        status, response = Client.delete_translation({"Id": "5eab1d602fecf51b250f31e4"}, {})

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_access_denied_for_registered(self, registered_headers):
        status, response = Client.delete_translation({"Id": "5eab1d602fecf51b250f31e4"}, registered_headers)

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_not_found(self):
        status, response = Client.delete_translation({"Id": "5eab1d602fecf51b250f31e4"})

        assert status
        assert response["Status"] == "Ok"

    def test_delete_ok(self, translation_data):
        _, response = Client.create_translation(translation_data)
        translation_id = response["Body"]["Id"]

        status, response = Client.delete_translation({ "Id": translation_id })
        assert status
        assert response["Status"] == "Ok"

        _, response = Client.get_translation_by_id({ "Id": translation_id })
        assert response["Status"] == "Error"
        assert response["Error"] == "NotFound"

    def test_edit_access_denied_for_unregistered(self):
        translation = Fake.translation()
        translation["Id"] = "5eab1d602fecf51b250f31e4"
        status, response = Client.edit_translation(translation, {})

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_access_denied_for_registered(self, registered_headers):
        translation = Fake.translation()
        translation["Id"] = "5eab1d602fecf51b250f31e4"
        status, response = Client.edit_translation(translation, registered_headers)

        assert status
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_validation_error_required(self):
        translation = Fake.translation()
        _, response = Client.create_translation(translation)
        translation = { "Id": response["Body"]["Id"] }

        status, response = Client.edit_translation(translation)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("ValueTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

    def test_edit_validation_error_same(self):
        translation1 = Fake.translation()
        _, response = Client.create_translation(translation1)
        translation1["Id"] = response["Body"]["Id"]

        translation2 = Fake.translation()
        _, response = Client.create_translation(translation2)
        translation2["Id"] = translation1["Id"]

        status, response = Client.edit_translation(translation2)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "AlreadyExists"

    def test_edit_ok(self):
        translation = Fake.translation()
        _, response = Client.create_translation(translation)
        translation["Id"] = response["Body"]["Id"]
        translation["Frequency"] = 12345

        status, response = Client.edit_translation(translation)
        assert status
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == translation["Id"]

        _, response = Client.get_translation_by_id({ "Id": translation["Id"] })
        assert response["Status"] == "Ok"
        assert response["Body"] == translation

