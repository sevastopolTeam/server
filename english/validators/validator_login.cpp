#include "validator_login.h"

#include "english/records/user_record.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    TValidatorLogin::TValidatorLogin(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
    }

    bool TValidatorLogin::Validate(const TMaybe<TRecordUser>& user) {
        int isValid = 1;

        isValid &= ValidateRequired(RECORD_USER_FIELD_EMAIL);
        isValid &= ValidateEmail(RECORD_USER_FIELD_EMAIL);
        isValid &= ValidateEmailExists(user);

        isValid &= ValidateRequired(RECORD_USER_FIELD_PASSWORD);
        isValid &= ValidateCorrectPassword(user);

        return (bool)isValid;
    }

    bool TValidatorLogin::ValidateEmailExists(const TMaybe<TRecordUser>& user) {
        if (!user) {
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_NOT_FOUND);
            return false;
        }

        return true;
    }

    bool TValidatorLogin::ValidateCorrectPassword(const TMaybe<TRecordUser>& user) {
        if (user && !user->CheckPassword(OriginJson.value(RECORD_USER_FIELD_PASSWORD, ""))) {
            ValidationErrors[RECORD_USER_FIELD_PASSWORD].push_back(VALIDATION_ERROR_INCORRECT);
            return false;
        }

        return true;
    }
}
