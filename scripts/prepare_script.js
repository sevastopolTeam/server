db.dropDatabase()
db.english_user.update(
    {
        "Email": "test@test.ru"
    }, {
        "Email": "test@test.ru",
        "Role": "Admin",
        "Name": "Test",
        "Confirmed": true,
        "ConfirmationKey": "",
        "PasswordHash": "",
        "Phone": "",
        "ResetPasswordKey": ""
    }, {
        "upsert": true
    }
);
