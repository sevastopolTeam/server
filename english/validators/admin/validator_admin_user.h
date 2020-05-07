#pragma once

#include "english/validators/validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "english/collections/user_collection.h"

namespace NEnglish {

    class TValidatorAdminUser : public IValidatorCommonEnglish {
    public:
        TValidatorAdminUser(const NJson::TJsonValue& jsonData);
        bool Validate(TCollectionUser& collectionUser);
        bool ValidateExists(TCollectionUser& collectionUser);
    };
}
