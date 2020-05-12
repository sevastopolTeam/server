import json
import random
import sys
import os
import pytest

sys.path.append(os.path.join(sys.path[0], '../../../scripts/english'))

from data_generator import Fake
from client import Client

API_URL = "http://localhost:5050/api/"

class TestAdminWordCategories:

    def setup_method(self, method):
        client = Client(API_URL)
        client.clear_word_categories(client.admin_headers())

    @pytest.fixture()
    def client(self, request):
        return Client(API_URL)

    # create
    def test_create_access_denied_for_not_registered_user(self, client):
        response = client.create_word_category({}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_access_denied_for_registered_user(self, client):
        response = client.create_word_category({}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_validation_error_required(self, client):
        response = client.create_word_category({}, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Name")[0] == "CanNotBeEmpty"

    def test_create_validation_error_same(self, client):
        word_category = Fake.word_category()
        client.create_word_category(word_category, client.admin_headers())
        response = client.create_word_category(word_category, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Name")[0] == "AlreadyExists"

    def test_create_ok(self, client):
        response = client.create_word_category(Fake.word_category(), client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "Ok"

    # get
    def test_get_access_denied_for_not_registered_user(self, client):
        response = client.get_word_categories({}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_access_denied_for_registered(self, client):
        response = client.get_word_categories({}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_empty(self, client):
        response = client.get_word_categories({}, client.admin_headers())
        
        assert response["status_code"] == 200
        assert int(response["Body"]["RecordsCount"]) == 0
        assert not response["Body"]["Records"]

    def test_get_some(self, client):
        word_categories_count = 10
        for i in range(word_categories_count):
            client.create_word_category(Fake.word_category(), client.admin_headers())

        response = client.get_word_categories({}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == word_categories_count
        assert len(response["Body"]["Records"]) == word_categories_count

    def test_get_with_pagination(self, client):
        word_categories_count = 10
        for i in range(word_categories_count):
            client.create_word_category(Fake.word_category(), client.admin_headers())

        response = client.get_word_categories({"PageSize": 5, "Page": 0}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == word_categories_count
        assert len(response["Body"]["Records"]) == 5

        response = client.get_word_categories({"PageSize": 8, "Page": 1}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == word_categories_count
        assert len(response["Body"]["Records"]) == 2

        response = client.get_word_categories({"PageSize": 2, "Page": 9}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == word_categories_count
        assert not response["Body"]["Records"]

    # delete
    def test_delete_access_denied_for_unregistered(self, client):
        response = client.delete_word_category({"Id": "5eab1d602fecf51b250f31e4"}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_access_denied_for_registered(self, client):
        response = client.delete_word_category({"Id": "5eab1d602fecf51b250f31e4"}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_not_found(self, client):
        response = client.delete_word_category({"Id": "5eab1d602fecf51b250f31e4"}, client.admin_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

    def test_delete_ok(self, client):
        word_category = Fake.word_category()
        response = client.create_word_category(word_category, client.admin_headers())
        word_category_id = response["Body"]["Id"]

        response = client.delete_word_category({ "Id": word_category_id }, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

        response = client.get_word_category_by_id({ "Id": word_category_id }, client.admin_headers())
        assert response["Status"] == "Error"
        assert response["Error"] == "NotFound"

    # edit
    def test_edit_access_denied_for_unregistered(self, client):
        word_category = Fake.word_category()
        word_category["Id"] = "5eab1d602fecf51b250f31e4"
        response = client.edit_word_category(word_category, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_access_denied_for_registered(self, client):
        word_category = Fake.word_category()
        word_category["Id"] = "5eab1d602fecf51b250f31e4"
        response = client.edit_word_category(word_category, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_validation_error_required(self, client):
        word_category = Fake.word_category()
        response = client.create_word_category(word_category, client.admin_headers())
        word_category = { "Id": response["Body"]["Id"] }

        response = client.edit_word_category(word_category, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Name")[0] == "CanNotBeEmpty"

    def test_edit_validation_error_same(self, client):
        word_category1 = Fake.word_category()
        response = client.create_word_category(word_category1, client.admin_headers())
        word_category1["Id"] = response["Body"]["Id"]

        word_category2 = Fake.word_category()
        response = client.create_word_category(word_category2, client.admin_headers())
        word_category2["Id"] = word_category1["Id"]

        response = client.edit_word_category(word_category2, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Name")[0] == "AlreadyExists"

    def test_edit_ok(self, client):
        word_category = Fake.word_category()
        response = client.create_word_category(word_category, client.admin_headers())
        word_category["Id"] = response["Body"]["Id"]
        word_category["Name"] = "edited_name"

        response = client.edit_word_category(word_category, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == word_category["Id"]

        response = client.get_word_category_by_id({ "Id": word_category["Id"] }, client.admin_headers())
        assert response["Status"] == "Ok"
        assert response["Body"] == word_category
