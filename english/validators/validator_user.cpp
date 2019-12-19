#include "validator_user.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorUser::TValidatorUser(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
    }

    bool TValidatorUser::Validate(TDataSource& dataSource) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_USER_FIELD_NAME);

        isValid &= ValidateRequired(RECORD_USER_FIELD_EMAIL);
        isValid &= ValidateEmail(RECORD_USER_FIELD_EMAIL);
        isValid &= ValidateEmailExists(dataSource);
        
        isValid &= ValidateRequired(RECORD_USER_FIELD_PHONE);
        isValid &= ValidatePhone(RECORD_USER_FIELD_PHONE);

        isValid &= ValidateRequired(RECORD_USER_FIELD_PASSWORD);

        isValid &= ValidateSame(RECORD_USER_FIELD_REPEAT_PASSWORD, RECORD_USER_FIELD_PASSWORD);
        return (bool)isValid;
    }

    bool TValidatorUser::ValidateEmailExists(TDataSource& dataSource) {
        bool valid = !dataSource.English.CollectionUser.ExistsWithEmail(
            NJson::GetString(OriginJson, RECORD_USER_FIELD_EMAIL, "")
        );
        if (!valid) {
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
