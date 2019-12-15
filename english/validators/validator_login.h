#pragma once

#include "validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "sources/data_source/data_source.h"

namespace NEnglish {

    class TValidatorLogin : public IValidatorCommonEnglish {
    public:
        TValidatorLogin(const NJson::TJsonValue& jsonData);
        
        bool Validate(TDataSource& dataSource, TRecordUser* user);
        void ValidateEmailExists(TRecordUser* user);
        void ValidateCorrectPassword(TRecordUser* user);
    };
}
