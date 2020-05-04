db.dropDatabase();

db.english_user.update(
    {
        "Email": "admin@admin.ru"
    }, {
        "Email": "admin@admin.ru",
        "Role": "Admin",
        "Name": "Admin",
        "Confirmed": true,
        "ConfirmationKey": "",
        "PasswordHash": "fb6eec8d965cbda47a36abf0d3b8bb01",
        "Phone": "+1234",
        "ResetPasswordKey": ""
    }, {
        "upsert": true
    }
);
