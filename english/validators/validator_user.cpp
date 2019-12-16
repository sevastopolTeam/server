#include "validator_user.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorUser::TValidatorUser(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
    }

    bool TValidatorUser::Validate(TDataSource& dataSource) {
        bool isValid = true;
        isValid = ValidateRequired(RECORD_USER_FIELD_NAME) && isValid;

        isValid = isValid && ValidateRequired(RECORD_USER_FIELD_EMAIL);
        isValid = isValid && ValidateEmail(RECORD_USER_FIELD_EMAIL);
        isValid = isValid && ValidateEmailExists(dataSource);
        
        isValid = isValid && ValidateRequired(RECORD_USER_FIELD_PHONE);
        isValid = isValid && ValidatePhone(RECORD_USER_FIELD_PHONE);

        isValid = isValid && ValidateRequired(RECORD_USER_FIELD_PASSWORD);

        isValid = isValid && ValidateSame(RECORD_USER_FIELD_REPEAT_PASSWORD, RECORD_USER_FIELD_PASSWORD);
        return isValid;
    }

    bool TValidatorUser::ValidateEmailExists(TDataSource& dataSource) {
        bool valid = !dataSource.English.CollectionUser.ExistsWithEmail(
            OriginJson.value(RECORD_USER_FIELD_EMAIL, "")
        );
        if (!valid) {
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
