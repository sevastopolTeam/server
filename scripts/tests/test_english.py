import requests
import json
import random
import sys
import os

sys.path.append(os.path.join(sys.path[0], '../'))

from data_generator import Fake

API_URL = "http://localhost:1234/api/"

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"
PATH_TO_ADMIN_TRANSLATIONS = "english/admin/translations"

def post_request(url, data, headers = {}):
    r = requests.post(url, data=json.dumps(data), headers=headers)
    if r.status_code == 200:
        return [True, r.json()]
    else:
        return [False, r.status_code]

def filter_dict(input, keys):
    return { key: input.get(key) for key in keys }

def register_user(user):
    return post_request(
        API_URL + PATH_TO_REGISTER_USER,
        user
    )

def login_user(user):
    return post_request(
        API_URL + PATH_TO_LOGIN_USER,
        user
    )

def login_as_admin():
    res = post_request(
        API_URL + PATH_TO_LOGIN_USER,
        {
            "Email": "buriksurik@mail.ru",
            "Password": "123"
        }
    )

    return res[1]["Body"]["SessionToken"]



RESPONSE_STATUS = "Status"
RESPONSE_VALIDATION_ERRORS = "ValidationErrors"
RESPONSE_ERROR = "Error"
RESPONSE_BODY = "Body"
RESPONSE_STATUS_OK = "Ok"
RESPONSE_STATUS_ERROR = "Error"
RESPONSE_STATUS_VALIDATION_ERROR = "ValidationError"
RESPONSE_STATUS_FATAL_ERROR = "FatalError"
RESPONSE_ERROR_INSERT = "InsertError"
RESPONSE_ERROR_ACCESS_DENIED = "AccessDenied"

VALIDATION_ERROR_REQUIRED = "CanNotBeEmpty"
VALIDATION_ERROR_EMAIL = "MustBeEmail"
VALIDATION_ERROR_SAME = "MustBeSame"
VALIDATION_ERROR_ALREADY_EXISTS = "AlreadyExists"
VALIDATION_ERROR_INCORRECT = "Incorrect"
VALIDATION_ERROR_NOT_FOUND = "NotFound"
VALIDATION_ERROR_PHONE = "MustBePhone"

RECORD_USER_FIELD_ID = "Id"
RECORD_USER_FIELD_EMAIL = "Email"
RECORD_USER_FIELD_NAME = "Name"
RECORD_USER_FIELD_PHONE = "Phone"
RECORD_USER_FIELD_PASSWORD_HASH = "PasswordHash"
RECORD_USER_FIELD_CONFIRMATION_KEY = "ConfirmationKey"
RECORD_USER_FIELD_CONFIRMED = "Confirmed"
RECORD_USER_FIELD_RESET_PASSWORD_KEY = "ResetPasswordKey"
RECORD_USER_FIELD_PASSWORD = "Password"
RECORD_USER_FIELD_REPEAT_PASSWORD = "RepeatPassword"
RECORD_USER_FIELD_ROLE = "Role"

RECORD_SESSION_FIELD_USER_ID = "UserId"
RECORD_SESSION_FIELD_TOKEN = "Token"

class TestEnglish:

    def test_register_empty_user(self):
        status, response = register_user({})

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response.get(RESPONSE_VALIDATION_ERRORS), dict)

        validation_errors = response.get(RESPONSE_VALIDATION_ERRORS)

        assert validation_errors.get(RECORD_USER_FIELD_EMAIL)[0] == VALIDATION_ERROR_REQUIRED
        assert validation_errors.get(RECORD_USER_FIELD_NAME)[0] == VALIDATION_ERROR_REQUIRED
        assert validation_errors.get(RECORD_USER_FIELD_PHONE)[0] == VALIDATION_ERROR_REQUIRED
        assert validation_errors.get(RECORD_USER_FIELD_PASSWORD)[0] == VALIDATION_ERROR_REQUIRED

    def test_register_wrong_user(self):
        status, response = register_user({
            RECORD_USER_FIELD_EMAIL: Fake.string(10),
            RECORD_USER_FIELD_NAME: Fake.name(),
            RECORD_USER_FIELD_PHONE: Fake.string(5),
            RECORD_USER_FIELD_PASSWORD: Fake.password(),
            RECORD_USER_FIELD_REPEAT_PASSWORD: Fake.password()
        })

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response.get(RESPONSE_VALIDATION_ERRORS), dict)

        validation_errors = response.get(RESPONSE_VALIDATION_ERRORS)

        assert validation_errors.get(RECORD_USER_FIELD_EMAIL)[0] == VALIDATION_ERROR_EMAIL
        assert validation_errors.get(RECORD_USER_FIELD_PHONE)[0] == VALIDATION_ERROR_PHONE
        assert validation_errors.get(RECORD_USER_FIELD_REPEAT_PASSWORD)[0] == VALIDATION_ERROR_SAME

    def test_register_exist_user(self):
        user = Fake.user()

        status1, response1 = register_user(user)
        status2, response2 = register_user(user)

        assert status1
        assert status2
        assert response1.get(RESPONSE_STATUS) == RESPONSE_STATUS_OK
        assert response2.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response2.get(RESPONSE_VALIDATION_ERRORS), dict)

        validation_errors = response2.get(RESPONSE_VALIDATION_ERRORS)

        assert validation_errors.get(RECORD_USER_FIELD_EMAIL)[0] == VALIDATION_ERROR_ALREADY_EXISTS

    def test_register_different_passwords_user(self):
        user = Fake.user()
        user[RECORD_USER_FIELD_REPEAT_PASSWORD] = Fake.password()
        status, response = register_user(user)

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response.get(RESPONSE_VALIDATION_ERRORS), dict)

        validation_errors = response.get(RESPONSE_VALIDATION_ERRORS)

        assert validation_errors.get(RECORD_USER_FIELD_REPEAT_PASSWORD)[0] == VALIDATION_ERROR_SAME

    def test_register_valid_user(self):
        status, response = register_user(Fake.user())

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_OK

    def test_login_empty_user(self):
        status, response = login_user({})

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response.get(RESPONSE_VALIDATION_ERRORS), dict)

        validation_errors = response.get(RESPONSE_VALIDATION_ERRORS)

        assert validation_errors.get(RECORD_USER_FIELD_EMAIL)[0] == VALIDATION_ERROR_REQUIRED
        assert validation_errors.get(RECORD_USER_FIELD_PASSWORD)[0] == VALIDATION_ERROR_REQUIRED

    def test_login_not_found_user(self):
        status, response = login_user({
            RECORD_USER_FIELD_EMAIL: Fake.email(),
            RECORD_USER_FIELD_PASSWORD: Fake.password()
        })

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response.get(RESPONSE_VALIDATION_ERRORS), dict)

        validation_errors = response.get(RESPONSE_VALIDATION_ERRORS)

        assert validation_errors.get(RECORD_USER_FIELD_EMAIL)[0] == VALIDATION_ERROR_NOT_FOUND

    def test_login_password_is_incorrect_user(self):
        user = Fake.user()
        register_user(user)

        test_user = user.copy()
        test_user[RECORD_USER_FIELD_PASSWORD] = Fake.password()
        status, response = login_user(test_user)

        assert status
        assert response.get(RESPONSE_STATUS) == RESPONSE_STATUS_VALIDATION_ERROR
        assert isinstance(response.get(RESPONSE_VALIDATION_ERRORS), dict)
        validation_errors = response.get(RESPONSE_VALIDATION_ERRORS)
        assert validation_errors.get(RECORD_USER_FIELD_PASSWORD)[0] == VALIDATION_ERROR_INCORRECT

    def test_login_valid_user(self):
        user = Fake.user()
        register_user(user)
        status, response = login_user(user)

        assert status
        assert len(response["Body"]["SessionToken"]) == 42

    def test_login_as_admin(self):
        token = login_as_admin()
        print("test")
        
        assert len(token) == 42

    def test_access_denied_to_translations_index(self):
        user = Fake.user()
        register_user(user)
        response = login_user(user)[1]
        status, response = post_request(API_URL + PATH_TO_ADMIN_TRANSLATIONS, {}, { "Authorization": response["Body"]["SessionToken"]})
        assert response["Status"] == RESPONSE_STATUS_ERROR
        assert response["Error"] == RESPONSE_ERROR_ACCESS_DENIED

