#pragma once

#include "validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

namespace NEnglish {

    class TValidatorLogin : public IValidatorCommonEnglish {
    public:
        TValidatorLogin(const NJson::TJsonValue& jsonData);
        
        bool Validate(const TMaybe<TRecordUser>& user);
        bool ValidateEmailExists(const TMaybe<TRecordUser>& user);
        bool ValidateCorrectPassword(const TMaybe<TRecordUser>& user);
    };
}
