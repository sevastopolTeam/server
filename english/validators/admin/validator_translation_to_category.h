#pragma once

#include "english/validators/validator_common_english.h"
#include "english/collections/translation_to_category_collection.h"

#include "contrib/json/json.h"
#include "util/generic/vector.h"


namespace NEnglish {

    class TValidatorTranslationToCategory : public IValidatorCommonEnglish {
    public:
        TValidatorTranslationToCategory(const NJson::TJsonValue& jsonData);
        bool Validate(TCollectionTranslationToCategory& collection);
        bool ValidateExists(TCollectionTranslationToCategory& collection);
        bool ValidateExistingTranslationId(TCollectionTranslationToCategory& collection);
        bool ValidateExistingWordCategoryId(TCollectionTranslationToCategory& collection);
    };
}
