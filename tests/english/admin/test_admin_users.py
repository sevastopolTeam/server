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
        client.clear_users(client.admin_headers())

    @pytest.fixture()
    def client(self, request):
        return Client(API_URL)

    # create
    def test_create_access_denied_for_not_registered_user(self, client):
        response = client.create_user({}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_access_denied_for_registered_user(self, client):
        response = client.create_user({}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_create_validation_error_required(self, client):
        response = client.create_user({}, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Name")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Email")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Phone")[0] == "CanNotBeEmpty"

    def test_create_with_incorrect_email(self, client):
        user = Fake.user()
        user["Email"] = "test"
        response = client.create_user(user, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Email")[0] == "MustBeEmail"

        user["Email"] = "1233"
        response = client.create_user(user, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Email")[0] == "MustBeEmail"

    def test_create_with_incorrect_phone(self, client):
        user = Fake.user()
        user["Phone"] = "test"
        response = client.create_user(user, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Phone")[0] == "MustBePhone"

        user["Phone"] = "1234567"
        response = client.create_user(user, client.admin_headers())
        assert response.get("Status") == "ValidationError"
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Phone")[0] == "MustBePhone"

    def test_create_validation_error_same(self, client):
        user = Fake.user()
        client.create_user(user, client.admin_headers())
        response = client.create_user(user, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Email")[0] == "AlreadyExists"

    def test_create_ok(self, client):
        response = client.create_user(Fake.user(), client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "Ok"

    # get
    def test_get_access_denied_for_not_registered_user(self, client):
        response = client.get_users({}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_access_denied_for_registered(self, client):
        response = client.get_users({}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_get_empty(self, client):
        response = client.get_users({}, client.admin_headers())
        
        assert response["status_code"] == 200
        assert int(response["Body"]["RecordsCount"]) == 1 # there is admin always
        assert not response["Body"]["Records"]

    def test_get_some(self, client):
        users_count = 10
        for i in range(users_count):
            client.create_user(Fake.user(), client.admin_headers())

        response = client.get_users({}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == users_count + 1
        assert len(response["Body"]["Records"]) == users_count + 1

    def test_get_with_pagination(self, client):
        users_count = 10
        for i in range(users_count):
            client.create_user(Fake.user(), client.admin_headers())

        response = client.get_users({"PageSize": 5, "Page": 0}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == users_count + 1
        assert len(response["Body"]["Records"]) == 5

        response = client.get_users({"PageSize": 8, "Page": 1}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == users_count + 1
        assert len(response["Body"]["Records"]) == 2

        response = client.get_users({"PageSize": 2, "Page": 9}, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Body"]["RecordsCount"] == users_count + 1
        assert not response["Body"]["Records"]

    # delete
    def test_delete_access_denied_for_unregistered(self, client):
        response = client.delete_user({"Id": "5eab1d602fecf51b250f31e4"}, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_access_denied_for_registered(self, client):
        response = client.delete_user({"Id": "5eab1d602fecf51b250f31e4"}, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_delete_not_found(self, client):
        response = client.delete_user({"Id": "5eab1d602fecf51b250f31e4"}, client.admin_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

    def test_delete_ok(self, client):
        user = Fake.user()
        response = client.create_user(user, client.admin_headers())
        user_id = response["Body"]["Id"]

        response = client.delete_user({ "Id": user_id }, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

        response = client.get_user_by_id({ "Id": user_id }, client.admin_headers())
        assert response["Status"] == "Error"
        assert response["Error"] == "NotFound"

    # edit
    def test_edit_access_denied_for_unregistered(self, client):
        user = Fake.user()
        user["Id"] = "5eab1d602fecf51b250f31e4"
        response = client.edit_user(user, {})

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_access_denied_for_registered(self, client):
        user = Fake.user()
        user["Id"] = "5eab1d602fecf51b250f31e4"
        response = client.edit_user(user, client.registered_headers())

        assert response["status_code"] == 200
        assert response["Status"] == "Error"
        assert response["Error"] == "AccessDenied"

    def test_edit_validation_error_required(self, client):
        user = Fake.user()
        response = client.create_user(user, client.admin_headers())
        user = { "Id": response["Body"]["Id"] }

        response = client.edit_user(user, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Name")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Email")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Phone")[0] == "CanNotBeEmpty"

    def test_edit_validation_error_same(self, client):
        user1 = Fake.user()
        response = client.create_user(user1, client.admin_headers())
        user1["Id"] = response["Body"]["Id"]

        user2 = Fake.user()
        response = client.create_user(user2, client.admin_headers())
        user2["Id"] = user1["Id"]

        response = client.edit_user(user2, client.admin_headers())

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("ValueFrom")[0] == "AlreadyExists"

    def test_edit_ok(self, client):
        user = Fake.user()
        response = client.create_user(user, client.admin_headers())
        user["Id"] = response["Body"]["Id"]
        user["Name"] = "EditedName"

        response = client.edit_user(user, client.admin_headers())
        assert response["status_code"] == 200
        assert response["Status"] == "Ok"
        assert response["Body"]["Id"] == user["Id"]

        response = client.get_user_by_id({ "Id": user["Id"] }, client.admin_headers())
        assert response["Status"] == "Ok"
        assert response["Body"] == user
