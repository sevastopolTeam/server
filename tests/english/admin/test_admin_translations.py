import json
import random
import sys
import os
import pytest

sys.path.append(os.path.join(sys.path[0], '../../../scripts/english'))

from data_generator import Fake
from client import Client

API_URL = "http://localhost:5050/api/"

class TestAdminTranslations:

    def setup_method(self, method):
        client = Client(API_URL)
        client.clear_translations(client.admin_headers())

    @pytest.fixture()
    def client(self, request):
        return Client(API_URL)

    # create
    def test_create_access_denied_for_not_registered_user(self, client):
        response = client.create_translation({}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_access_denied_for_registered_user(self, client):
        response = client.create_translation({}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_validation_error_required(self, client):
        response = client.create_translation({}, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("ValueTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

    def test_create_with_incorrect_frequency(self, client):
        translation = Fake.translation()
        translation["Frequency"] = "+"
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation["Frequency"] = "gfsfg"
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation["Frequency"] = "-03535"
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation["Frequency"] = ""
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

        translation["Frequency"] = "0.2525"
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeUnsignedInt"

        translation["Frequency"] = "9999999999"
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeLessThan"

        translation["Frequency"] = "945834863496394867389467398467398674999999999"
        response = client.create_translation(translation, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Frequency")[0] == "MustBeLessThan"

    def test_create_validation_error_same(self, client):
        translation = Fake.translation()
        client.create_translation(translation, client.admin_headers())
        response = client.create_translation(translation, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "AlreadyExists"

    def test_create_ok(self, client):
        response = client.create_translation(Fake.translation(), client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "Ok"

    def test_create_with_correct_frequency(self, client):
        response = client.create_translation(Fake.translation(), client.admin_headers())
        assert response["status_code"] == 200
        assert response.get("Status") == "Ok"
        translation_id = response["Body"]["Id"]
        response = client.get_translation_by_id({ "Id": translation_id }, client.admin_headers())
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == translation_id

    def test_create_with_zero_frequency(self, client):
        translation = Fake.translation()
        translation["Frequency"] = "0"
        response = client.create_translation(translation, client.admin_headers())
        assert response["status_code"] == 200
        assert response.get("Status") == "Ok"

        translation_id = response["Body"]["Id"]
        response = client.get_translation_by_id({ "Id": translation_id }, client.admin_headers())
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == translation_id

    # get
    def test_get_access_denied_for_not_registered_user(self, client):
        response = client.get_translations({}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_access_denied_for_registered(self, client):
        response = client.get_translations({}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_empty(self, client):
        response = client.get_translations({}, client.admin_headers())
        
        assert response["status_code"] == 200
        assert int(response["Body"]["RecordsCount"]) == 0
        assert not response["Body"]["Records"]

    def test_get_some(self, client):
        translations_count = 10
        for i in range(translations_count):
            client.create_translation(Fake.translation(), client.admin_headers())

        response = client.get_translations({}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == translations_count
        assert len(response["Body"]["Records"]) == translations_count

    def test_get_with_pagination(self, client):
        translations_count = 10
        for i in range(translations_count):
            client.create_translation(Fake.translation(), client.admin_headers())

        response = client.get_translations({"PageSize": 5, "Page": 0}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == translations_count
        assert len(response["Body"]["Records"]) == 5

        response = client.get_translations({"PageSize": 8, "Page": 1}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == translations_count
        assert len(response["Body"]["Records"]) == 2

        response = client.get_translations({"PageSize": 2, "Page": 9}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == translations_count
        assert not response["Body"]["Records"]

    # delete
    def test_delete_access_denied_for_unregistered(self, client):
        response = client.delete_translation({"Id": "5eab1d602fecf51b250f31e4"}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_access_denied_for_registered(self, client):
        response = client.delete_translation({"Id": "5eab1d602fecf51b250f31e4"}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_not_found(self, client):
        response = client.delete_translation({"Id": "5eab1d602fecf51b250f31e4"}, client.admin_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

    def test_delete_ok(self, client):
        translation = Fake.translation()
        response = client.create_translation(translation, client.admin_headers())
        translation_id = response["Body"]["Id"]

        response = client.delete_translation({ "Id": translation_id }, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

        response = client.get_translation_by_id({ "Id": translation_id }, client.admin_headers())
        assert response["Status"] == "Error"
        assert response["Error"] == "NotFound"

    # edit
    def test_edit_access_denied_for_unregistered(self, client):
        translation = Fake.translation()
        translation["Id"] = "5eab1d602fecf51b250f31e4"
        response = client.edit_translation(translation, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_access_denied_for_registered(self, client):
        translation = Fake.translation()
        translation["Id"] = "5eab1d602fecf51b250f31e4"
        response = client.edit_translation(translation, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_validation_error_required(self, client):
        translation = Fake.translation()
        response = client.create_translation(translation, client.admin_headers())
        translation = { "Id": response["Body"]["Id"] }

        response = client.edit_translation(translation, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("ValueTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageFrom")[0] == "CanNotBeEmpty"
        assert validation_errors.get("LanguageTo")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Frequency")[0] == "CanNotBeEmpty"

    def test_edit_validation_error_same(self, client):
        translation1 = Fake.translation()
        response = client.create_translation(translation1, client.admin_headers())
        translation1["Id"] = response["Body"]["Id"]

        translation2 = Fake.translation()
        response = client.create_translation(translation2, client.admin_headers())
        translation2["Id"] = translation1["Id"]

        response = client.edit_translation(translation2, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "AlreadyExists"

    def test_edit_ok(self, client):
        translation = Fake.translation()
        response = client.create_translation(translation, client.admin_headers())
        translation["Id"] = response["Body"]["Id"]
        translation["Frequency"] = 12345

        response = client.edit_translation(translation, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == translation["Id"]

        response = client.get_translation_by_id({ "Id": translation["Id"] }, client.admin_headers())
        assert response["Status"] == "Ok"
        assert response["Body"] == translation
