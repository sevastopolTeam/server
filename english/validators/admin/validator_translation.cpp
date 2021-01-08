#include "validator_translation.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorTranslation::TValidatorTranslation(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorTranslation::Validate(TCollectionTranslation& collectionTranslation) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_RUSSIAN);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_ENGLISH);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_FREQUENCY);
        isValid &= ValidateUnsignedInt(RECORD_TRANSLATION_FIELD_FREQUENCY);
        isValid &= ValidateLessThan(RECORD_TRANSLATION_FIELD_FREQUENCY, 1e9);
        isValid &= ValidateExists(collectionTranslation);

        return static_cast<bool>(isValid);
    }

    bool TValidatorTranslation::ValidateExists(TCollectionTranslation& collectionTranslation) {
        const auto foundRecord = collectionTranslation.FindByFullMatching(
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_RUSSIAN, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_ENGLISH, "")
        );

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_FIELD_ID, "")) {
            ValidationErrors[RECORD_TRANSLATION_FIELD_RUSSIAN].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
