#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"

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

    class TRecordUser : public IRecord {
    public:
        TRecordUser(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;

        NJson::TJsonValue GetUniqSelector() const;

    private:
        // DB fields
        TString Email;
        TString Name;
        TString Phone;
        TString PasswordHash;
        TString ConfirmationKey;
        bool Confirmed;
        TString ResetPasswordKey;

        // extra fields
        TString Password;
        TString RepeatPassword;
    };
}