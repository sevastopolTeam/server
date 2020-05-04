#include "validator_word_category.h"

#include "english/records/word_category_record.h"

namespace NEnglish {

    TValidatorWordCategory::TValidatorWordCategory(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorWordCategory::Validate(TCollectionWordCategory& collection) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_WORD_CATEGORY_FIELD_NAME);
        isValid &= ValidateExists(collection);

        return static_cast<bool>(isValid);
    }

    bool TValidatorWordCategory::ValidateExists(TCollectionWordCategory& collection) {
        const auto foundRecord = collection.FindByName(
            NJson::GetString(OriginJson, RECORD_WORD_CATEGORY_FIELD_NAME, "")
        );

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_FIELD_ID, "")) {
            ValidationErrors[RECORD_WORD_CATEGORY_FIELD_NAME].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
