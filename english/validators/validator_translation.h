#pragma once

#include "validator_common_english.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"

#include "english/collections/translation_collection.h"

class TCollectionTranslation;

namespace NEnglish {

    class TValidatorTranslation : public IValidatorCommonEnglish {
    public:
        TValidatorTranslation(const NJson::TJsonValue& jsonData);
        bool Validate(TCollectionTranslation& collectionTranslation);

    private:
        bool ValidateExists(TCollectionTranslation& collectionTranslation);
    };
}
