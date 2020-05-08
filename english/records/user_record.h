#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    const TString RECORD_USER_FIELD_EMAIL = "Email";
    const TString RECORD_USER_FIELD_NAME = "Name";
    const TString RECORD_USER_FIELD_PHONE = "Phone";
    const TString RECORD_USER_FIELD_PASSWORD_HASH = "PasswordHash";
    const TString RECORD_USER_FIELD_CONFIRMATION_KEY = "ConfirmationKey";
    const TString RECORD_USER_FIELD_CONFIRMED = "Confirmed";
    const TString RECORD_USER_FIELD_RESET_PASSWORD_KEY = "ResetPasswordKey";
    const TString RECORD_USER_FIELD_PASSWORD = "Password";
    const TString RECORD_USER_FIELD_REPEAT_PASSWORD = "RepeatPassword";
    const TString RECORD_USER_FIELD_ROLE = "Role";

    const TString USER_ROLE_ADMIN = "Admin";
    const TString USER_ROLE_USER = "User";

    class TRecordUser : public IRecord {
    public:
        TRecordUser() = default;
        TRecordUser(const NJson::TJsonValue& json);

        bool IsAdmin() const;        
        bool CheckPassword(const TString& password) const;
        NJson::TJsonValue ForDB() const override;
        NJson::TJsonValue ToJson() const override;

        void UpdateAdminFields(const NJson::TJsonValue& json);

    private:
        // DB fields
        TString Email;
        TString Name;
        TString Phone;
        TString PasswordHash;
        TString ConfirmationKey;
        bool Confirmed;
        TString ResetPasswordKey;
        TString Role;

        // extra fields
        TString Password;
        TString RepeatPassword;
    };
}
