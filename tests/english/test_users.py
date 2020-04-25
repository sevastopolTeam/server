import requests
import json
import random
import sys
import os
import pytest

from data_generator import Fake
from client import Client

@pytest.fixture()
def user(request):
    return Fake.user()

class TestUsers:

    def test_register_empty_user(self):
        status, response = Client.register_user({})

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Name")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Phone")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Password")[0] == "CanNotBeEmpty"

    def test_register_wrong_user(self):
        status, response = Client.register_user({
            "Email": Fake.string(10),
            "Name": Fake.name(),
            "Phone": Fake.string(5),
            "Password": Fake.password(),
            "RepeatPassword": Fake.password()
        })

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "MustBeEmail"
        assert validation_errors.get("Phone")[0] == "MustBePhone"
        assert validation_errors.get("RepeatPassword")[0] == "MustBeSame"

    def test_register_exist_user(self, user):
        status1, response1 = Client.register_user(user)
        status2, response2 = Client.register_user(user)

        assert status1
        assert status2
        assert response1.get("Status") == "Ok"
        assert response2.get("Status") == "ValidationError"
        assert isinstance(response2.get("ValidationErrors"), dict)

        validation_errors = response2.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "AlreadyExists"

    def test_register_different_passwords_user(self, user):
        user["RepeatPassword"] = Fake.password()
        status, response = Client.register_user(user)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("RepeatPassword")[0] == "MustBeSame"

    def test_register_valid_user(self, user):
        status, response = Client.register_user(user)

        assert status
        assert response.get("Status") == "Ok"

    def test_login_empty_user(self):
        status, response = Client.login_user({})

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "CanNotBeEmpty"
        assert validation_errors.get("Password")[0] == "CanNotBeEmpty"

    def test_login_not_found_user(self):
        status, response = Client.login_user({
            "Email": Fake.email(),
            "Password": Fake.password()
        })

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)

        validation_errors = response.get("ValidationErrors")

        assert validation_errors.get("Email")[0] == "NotFound"

    def test_login_password_is_incorrect_user(self, user):
        Client.register_user(user)

        test_user = user.copy()
        test_user["Password"] = Fake.password()
        status, response = Client.login_user(test_user)

        assert status
        assert response.get("Status") == "ValidationError"
        assert isinstance(response.get("ValidationErrors"), dict)
        validation_errors = response.get("ValidationErrors")
        assert validation_errors.get("Password")[0] == "Incorrect"

    def test_login_valid_user(self, user):
        Client.register_user(user)
        status, response = Client.login_user(user)

        assert status
        assert len(response["Body"]["SessionToken"]) == 42

    def test_logout(self, user):
        Client.register_user(user)
        response = Client.login_user(user)[1]
        status, response = Client.logout(response["Body"]["SessionToken"])

        assert status
        assert response["Status"] == "Ok"

