#pragma once

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "validator_common_english.h"

namespace NEnglish {

    class TValidatorLogin : public IValidatorCommonEnglish {
    public:
        TValidatorLogin(const NJson::TJsonValue& jsonData);
        bool Validate() override;
    };
}
