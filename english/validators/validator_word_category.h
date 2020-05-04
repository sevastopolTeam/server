#pragma once

#include "validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "english/collections/word_category_collection.h"

namespace NEnglish {

    class TValidatorWordCategory : public IValidatorCommonEnglish {
    public:
        TValidatorWordCategory(const NJson::TJsonValue& jsonData);
        bool Validate(TCollectionWordCategory& collection);
        bool ValidateExists(TCollectionWordCategory& collection);
    };
}
