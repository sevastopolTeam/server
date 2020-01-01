import requests
import json
import random

from random_generator import *

API_URL = "http://localhost:1234/api/"

PATH_TO_REGISTER_USER = "english/users"
PATH_TO_LOGIN_USER = "english/login"

VALIDATION_ERROR_REQUIRED = "CanNotBeEmpty";
VALIDATION_ERROR_EMAIL = "MustBeEmail";
VALIDATION_ERROR_SAME = "MustBeSame";
VALIDATION_ERROR_ALREADY_EXISTS = "AlreadyExists";
VALIDATION_ERROR_INCORRECT = "Incorrect";
VALIDATION_ERROR_NOT_FOUND = "NotFound";
VALIDATION_ERROR_PHONE = "MustBePhone"

RECORD_USER_FIELD_ID = "Id";
RECORD_USER_FIELD_EMAIL = "Email";
RECORD_USER_FIELD_NAME = "Name";
RECORD_USER_FIELD_PHONE = "Phone";
RECORD_USER_FIELD_PASSWORD_HASH = "PasswordHash";
RECORD_USER_FIELD_CONFIRMATION_KEY = "ConfirmationKey";
RECORD_USER_FIELD_CONFIRMED = "Confirmed";
RECORD_USER_FIELD_RESET_PASSWORD_KEY = "ResetPasswordKey";
RECORD_USER_FIELD_PASSWORD = "Password";
RECORD_USER_FIELD_REPEAT_PASSWORD = "RepeatPassword";
RECORD_USER_FIELD_ROLE = "Role";

RECORD_SESSION_FIELD_USER_ID = "UserId";
RECORD_SESSION_FIELD_TOKEN = "Token";

def error(msg):
    print("ERROR: " + str(msg))

def ok(msg = ""):
    print("OK " + str(msg))

def is_list(value):
    return isinstance(value, list)

def is_dict(value):
    return isinstance(value, dict)

def post_request(url, data):
    r = requests.post(url, data=json.dumps(data))
    if r.status_code == 200:
        return [True, r.json()]
    else:
        return [False, r.status_code]

def filter_dict(input, keys):
    return { key: input.get(key) for key in keys }

def register_user(user):
    return post_request(
        API_URL + PATH_TO_REGISTER_USER,
        filter_dict(user, [
            RECORD_USER_FIELD_EMAIL,
            RECORD_USER_FIELD_NAME,
            RECORD_USER_FIELD_PHONE,
            RECORD_USER_FIELD_PASSWORD,
            RECORD_USER_FIELD_REPEAT_PASSWORD
        ])
    )

def login_user(user):
    return post_request(
        API_URL + PATH_TO_LOGIN_USER,
        filter_dict(user, [RECORD_USER_FIELD_EMAIL, RECORD_USER_FIELD_PASSWORD])
    )

def test_register_empty_user():
    print("Test register empty user")
    status, response = register_user({})
    if not status:
        error("Response code is {code}".format(code = response))
        return

    if response.get("Status") != "ValidationError":
        error("Status must be ValidationError")
        return

    if not is_dict(response.get("ValidationErrors")):
        error("ValidationErrors must be dict")
        return

    validation_errors = response.get("ValidationErrors")

    if validation_errors.get(RECORD_USER_FIELD_EMAIL)[0] != VALIDATION_ERROR_REQUIRED:
        error("Validation Error for '{field}' must be '{expected}', but it is '{found}'".format(
            field = RECORD_USER_FIELD_EMAIL,
            expected = VALIDATION_ERROR_REQUIRED,
            found = validation_errors.get(RECORD_USER_FIELD_EMAIL)[0]
        ))

    if validation_errors.get(RECORD_USER_FIELD_NAME)[0] != VALIDATION_ERROR_REQUIRED:
        error("Validation Error for '{field}' must be '{expected}', but it is '{found}'".format(
            field = RECORD_USER_FIELD_NAME,
            expected = VALIDATION_ERROR_REQUIRED,
            found = validation_errors.get(RECORD_USER_FIELD_NAME)[0]
        ))
    if validation_errors.get(RECORD_USER_FIELD_PHONE)[0] != VALIDATION_ERROR_REQUIRED:
        error("Validation Error for '{field}' must be '{expected}', but it is '{found}'".format(
            field = RECORD_USER_FIELD_PHONE,
            expected = VALIDATION_ERROR_REQUIRED,
            found = validation_errors.get(RECORD_USER_FIELD_PHONE)[0]
        ))

    if validation_errors.get(RECORD_USER_FIELD_PASSWORD)[0] != VALIDATION_ERROR_REQUIRED:
        error("Validation Error for '{field}' must be '{expected}', but it is '{found}'".format(
            field = RECORD_USER_FIELD_PASSWORD,
            expected = VALIDATION_ERROR_REQUIRED,
            found = validation_errors.get(RECORD_USER_FIELD_PASSWORD)[0]
        ))

    ok()

def test_register_wrong_user():
    print("Test register wrong user")
    status, response = register_user({
        "Email": random_string(10),
        "Name": random_string(10),
        "Phone": random_string(9),
        "Password": random_string(10),
        "RepeatPassword": random_string(10)
    })

    if not status:
        error("Response code is " + str(response))
        return

    if response.get("Status") != "ValidationError":
        error("Status must be ValidationError")
        return

    if not is_dict(response.get("ValidationErrors")):
        error("ValidationErrors must be dict")
        return

    validation_errors = response.get("ValidationErrors")

    if validation_errors.get("Email")[0] != VALIDATION_ERROR_EMAIL:
        error("Validation Error for Email must be" + VALIDATION_ERROR_EMAIL)

    if validation_errors.get("Phone")[0] != VALIDATION_ERROR_PHONE:
        error("Validation Error for Phone must be" + VALIDATION_ERROR_PHONE)

    if validation_errors.get("RepeatPassword")[0] != "MustBeSame":
        error("Validation Error for RepeatPassword must be" + "MustBeSame")

    ok()

def test_register_exist_user():
    print("Test register exist user")
    user = random_user()

    status1, response1 = register_user(user)
    status2, response2 = register_user(user)

    if not status1 or not status2:
        error("Response code is " + str(response))
        return

    if response1.get("Status") != "Ok":
        error("Registration is not completed")
        return

    if response2.get("Status") != "ValidationError":
        error("Status must be ValidationError")
        return

    if not is_dict(response2.get("ValidationErrors")):
        error("ValidationErrors must be dict")
        return

    validation_errors = response2.get("ValidationErrors")

    if validation_errors.get("Email")[0] != "AlreadyExists":
        error("Validation Error for Email must be" + "AlreadyExists")

    ok()

def test_register_valid_user():
    print("Test register valid user")
    status, response = register_user(random_user())

    if not status:
        error("Response code is " + str(response))
        return

    if response.get("Status") != "Ok":
        error("Status must be Ok")
        return

    ok()

def test_login_empty_user():
    print("Test login empty user")
    status, response = login_user({})

    if not status:
        error("Response code is " + str(response))
        return

    if response.get("Status") != "ValidationError":
        error("Status must be ValidationError")
        return

    if not is_dict(response.get("ValidationErrors")):
        error("ValidationErrors must be dict")
        return

    validation_errors = response.get("ValidationErrors")

    if validation_errors.get("Email")[0] != VALIDATION_ERROR_REQUIRED:
        error("Validation Error for email must be" + VALIDATION_ERROR_REQUIRED)

    if validation_errors.get("Password")[0] != VALIDATION_ERROR_REQUIRED:
        error("Validation Error for Password must be" + VALIDATION_ERROR_REQUIRED)

    ok()

def test_login_not_found_user():
    print("Test login not found user")
    status, response = login_user({
        "Email": random_email(),
        "Password": random_string(10)
    })

    if not status:
        error("Response code is " + str(response))
        return

    if response.get("Status") != "ValidationError":
        error("Status must be ValidationError")
        return

    if not is_dict(response.get("ValidationErrors")):
        error("ValidationErrors must be dict")

    validation_errors = response.get("ValidationErrors")
    print(validation_errors)

    if validation_errors.get("Email")[0] != "NotFound":
        error("Validation Error for Email must be" + "NotFound")

    ok()

def test_login_password_is_incorrect_user(user):
    print("Test login password is incorrect user")
    test_user = user.copy()
    test_user["Password"] = random_string(5)
    status, response = login_user(test_user)

    if not status:
        error("Response code is " + str(response))
        return

    if response.get("Status") != "ValidationError":
        error("Status must be ValidationError")
        return

    if not is_dict(response.get("ValidationErrors")):
        error("ValidationErrors must be dict")
        return

    validation_errors = response.get("ValidationErrors")
    
    if validation_errors.get("Password")[0] != "Incorrect":
        error("Validation Error for Email must be" + "NotFound")

    ok()

def tests_for_register_user():
    test_register_empty_user()
    test_register_wrong_user()
    test_register_exist_user()
    test_register_valid_user()

def tests_for_login_user():
    user = random_user()
    register_user(user)

    test_login_empty_user()
    test_login_not_found_user()
    test_login_password_is_incorrect_user(user)

def main():
    print("Task is started")
    
    tests_for_register_user()
    tests_for_login_user()

    print("Task is finished")

main()
