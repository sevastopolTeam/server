#pragma once

#include "validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "english/collections/user_collection.h"

namespace NEnglish {

    class TValidatorUser : public IValidatorCommonEnglish {
    public:
        TValidatorUser(const NJson::TJsonValue& jsonData);
        bool Validate(TCollectionUser& collectionUser);
        bool ValidateEmailExists(TCollectionUser& collectionUser);
    };
}
