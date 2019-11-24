#include "validator_user.h"

#include "english/records/user_record.h"

#include "util/generic/iostream.h"


namespace NEnglish {

    TValidatorUser::TValidatorUser(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
        IsValid = false;
    }

    bool TValidatorUser::Validate() {
        IsValid = true;
        ValidateRequired(RECORD_USER_FIELD_NAME);

        ValidateRequired(RECORD_USER_FIELD_EMAIL);
        ValidateEmail(RECORD_USER_FIELD_EMAIL);

        ValidateRequired(RECORD_USER_FIELD_PHONE);
        ValidatePhone(RECORD_USER_FIELD_PHONE);

        ValidateRequired(RECORD_USER_FIELD_PASSWORD);

        ValidateSame(RECORD_USER_FIELD_REPEAT_PASSWORD, RECORD_USER_FIELD_PASSWORD);

        return IsValid;
    }
}
