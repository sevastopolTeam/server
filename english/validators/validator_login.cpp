#include "validator_login.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorLogin::TValidatorLogin(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
        IsValid = false;
    }

    bool TValidatorLogin::Validate(TDataSource& dataSource, TMaybe<TRecordUser>& user) {
        IsValid = true;
        user = dataSource.English.CollectionUser.FindByEmail(
            OriginJson.value(RECORD_USER_FIELD_EMAIL, "")
        );

        ValidateRequired(RECORD_USER_FIELD_EMAIL);
        ValidateEmail(RECORD_USER_FIELD_EMAIL);
        ValidateEmailExists(user);

        ValidateRequired(RECORD_USER_FIELD_PASSWORD);
        ValidateCorrectPassword(user);

        return IsValid;
    }

    bool TValidatorLogin::ValidateEmailExists(TMaybe<TRecordUser>& user) {
        bool valid = !user.Empty();
        if (!valid) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_NOT_FOUND);
        }
        return valid;
    }

    bool TValidatorLogin::ValidateCorrectPassword(TMaybe<TRecordUser>& user) {
        bool valid = user.Empty() || user->CheckPassword(OriginJson.value(RECORD_USER_FIELD_PASSWORD, ""));
        if (!valid) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_PASSWORD].push_back(VALIDATION_ERROR_INCORRECT);
        }

        return valid;
    }
}
