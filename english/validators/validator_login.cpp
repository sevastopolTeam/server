#include "validator_login.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorLogin::TValidatorLogin(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
        Valid = false;
    }

    bool TValidatorLogin::Validate() {
        Valid = true;

        ValidateRequired(RECORD_USER_FIELD_EMAIL);
        ValidateEmail(RECORD_USER_FIELD_EMAIL);

        ValidateRequired(RECORD_USER_FIELD_PASSWORD);

        return Valid;
    }
}
