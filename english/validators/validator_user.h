#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

#include "validator_common_english.h"

namespace NEnglish {

    class TValidatorUser : public IValidatorCommonEnglish {
    public:
        TValidatorUser(const NJson::TJsonValue& jsonData);
        bool Validate() override;
    };
}
