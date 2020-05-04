#include "validator_translation.h"

#include "english/records/translation_record.h"

namespace NEnglish {

    TMaybe<TRecordTranslation> FindByFullMatching(const NJson::TJsonValue&, const NJson::TJsonValue&, const NJson::TJsonValue&, const NJson::TJsonValue&);

    TValidatorTranslation::TValidatorTranslation(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorTranslation::Validate(TCollectionTranslation& collectionTranslation) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_VALUE_FROM);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_VALUE_TO);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_LANGUAGE_FROM);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_LANGUAGE_TO);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_FREQUENCY);
        isValid &= ValidateUnsignedInt(RECORD_TRANSLATION_FIELD_FREQUENCY);
        isValid &= ValidateLessThan(RECORD_TRANSLATION_FIELD_FREQUENCY, 1e9);
        isValid &= ValidateExists(collectionTranslation);

        return static_cast<bool>(isValid);
    }

    bool TValidatorTranslation::ValidateExists(TCollectionTranslation& collectionTranslation) {
        const auto foundRecord = collectionTranslation.FindByFullMatching(
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_VALUE_FROM, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_VALUE_TO, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_LANGUAGE_TO, "")
        );

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_FIELD_ID, "")) {
            ValidationErrors[RECORD_TRANSLATION_FIELD_VALUE_FROM].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
