#include "validator_login.h"

#include "english/records/user_record.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    TValidatorLogin::TValidatorLogin(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
        IsValid = false;
    }

    bool TValidatorLogin::Validate(TDataSource& dataSource, TRecordUser* user) {
        IsValid = true;
        TRecordUser* foundUser = dataSource.English.CollectionUser.FindByEmail(
            OriginJson.value(RECORD_USER_FIELD_EMAIL, "")
        ).Get();

        ValidateRequired(RECORD_USER_FIELD_EMAIL);
        ValidateEmail(RECORD_USER_FIELD_EMAIL);
        ValidateEmailExists(foundUser);

        ValidateRequired(RECORD_USER_FIELD_PASSWORD);
        ValidateCorrectPassword(foundUser);

        if (!!foundUser) {
            *user = *foundUser;
        }
        return IsValid;
    }

    bool TValidatorLogin::ValidateEmailExists(TRecordUser* user) {
        bool valid = !!user;
        if (!valid) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_NOT_FOUND);
        }
        return valid;
    }

    bool TValidatorLogin::ValidateCorrectPassword(TRecordUser* user) {
        bool valid = !user || user->CheckPassword(OriginJson.value(RECORD_USER_FIELD_PASSWORD, ""));
        if (!valid) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_PASSWORD].push_back(VALIDATION_ERROR_INCORRECT);
        }

        return valid;
    }
}
