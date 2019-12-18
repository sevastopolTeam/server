#pragma once

#include "validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "sources/data_source/data_source.h"

namespace NEnglish {

    class TValidatorUser : public IValidatorCommonEnglish {
    public:
        TValidatorUser(const NJson::TJsonValue& jsonData);
        bool Validate(TDataSource& dataSource);
        bool ValidateEmailExists(TDataSource& dataSource);
    };
}
