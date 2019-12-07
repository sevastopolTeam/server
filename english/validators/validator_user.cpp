#include "validator_user.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorUser::TValidatorUser(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
        IsValid = false;
    }

    bool TValidatorUser::Validate(TDataSource& dataSource) {
        IsValid = true;
        ValidateRequired(RECORD_USER_FIELD_NAME);

        ValidateRequired(RECORD_USER_FIELD_EMAIL);
        ValidateEmail(RECORD_USER_FIELD_EMAIL);
        ValidateEmailExists(dataSource);
        
        ValidateRequired(RECORD_USER_FIELD_PHONE);
        ValidatePhone(RECORD_USER_FIELD_PHONE);

        ValidateRequired(RECORD_USER_FIELD_PASSWORD);

        ValidateSame(RECORD_USER_FIELD_REPEAT_PASSWORD, RECORD_USER_FIELD_PASSWORD);
        return IsValid;
    }

    bool TValidatorUser::ValidateEmailExists(TDataSource& dataSource) {
        bool valid = !dataSource.English.CollectionUser.ExistsWithEmail(
            OriginJson.value(RECORD_USER_FIELD_EMAIL, "")
        );
        if (!valid) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
        }

        return valid;
    }
}
