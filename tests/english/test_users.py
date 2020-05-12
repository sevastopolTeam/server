import requests
import json
import random
import sys
import os
import pytest

sys.path.append(os.path.join(sys.path[0], '../../scripts/english'))

from data_generator import Fake
from client import Client

API_URL = "http://localhost:5050/api/"

class TestUsers:

    @pytest.fixture()
    def client(self, request):
        return Client(API_URL)

    def test_register_empty_user(self, client):
        response = client.register_user({})

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Name")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Phone")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Password")[0] == "CanNotBeEmpty"

    def test_register_wrong_user(self, client):
        response = client.register_user({
            "Email": Fake.string(10),
            "Name": Fake.name(),
            "Phone": Fake.string(5),
            "Password": Fake.password(),
            "RepeatPassword": Fake.password()
        })

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "MustBeEmail"
        assert validation_errors.get("Phone")[0] == "MustBePhone"
        assert validation_errors.get("RepeatPassword")[0] == "MustBeSame"

    def test_register_exist_user(self, client):
        user = Fake.user()
        response1 = client.register_user(user)
        response2 = client.register_user(user)

        assert response1["status_code"] == 200
        assert response1["status_code"] == 200
        assert response1.get("Status") == "Ok"
        assert response2.get("Status") == "ValidationError"
        assert isinstance(response2.get("ValidationErrors"), dict)

        validation_errors = response2.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "AlreadyExists"

    def test_register_different_passwords_user(self, client):
        user = Fake.user()
        user["RepeatPassword"] = Fake.password()
        response = client.register_user(user)

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("RepeatPassword")[0] == "MustBeSame"

    def test_register_valid_user(self, client):
        user = Fake.user()
        response = client.register_user(user)

        assert response["status_code"] == 200
        assert response.get("Status") == "Ok"

    def test_login_empty_user(self, client):
        response = client.login_user({})

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Password")[0] == "CanNotBeEmpty"

    def test_login_not_found_user(self, client):
        response = client.login_user({
            "Email": Fake.email(),
            "Password": Fake.password()
        })

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "NotFound"

    def test_login_password_is_incorrect_user(self, client):
        user = Fake.user()
        client.register_user(user)

        test_user = user.copy()
        test_user["Password"] = Fake.password()
        response = client.login_user(test_user)

        assert response["status_code"] == 200
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Password")[0] == "Incorrect"

    def test_login_valid_user(self, client):
        user = Fake.user()
        client.register_user(user)
        response = client.login_user(user)

        assert response["status_code"] == 200
        assert len(response["Body"]["SessionToken"]) == 42

    def test_logout(self, client):
        user = Fake.user()
        client.register_user(user)
        response = client.login_user(user)
        response = client.logout({"Authorization": response["Body"]["SessionToken"]})

        assert response["status_code"] == 200
        assert response["Status"] == "Ok"

