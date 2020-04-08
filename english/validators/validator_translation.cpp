#include "validator_translation.h"

#include "english/records/translation_record.h"

namespace NEnglish {

    TValidatorTranslation::TValidatorTranslation(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorTranslation::Validate(TDataSource& dataSource) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_VALUE_FROM);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_VALUE_TO);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_LANGUAGE_FROM);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_LANGUAGE_TO);
        return static_cast<bool>(isValid);
    }

    bool TValidatorTranslation::ValidateExists(TDataSource& dataSource) {
        const auto foundRecord = dataSource.English.CollectionTranslation.FindByFullMatching(
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_VALUE_FROM, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_VALUE_TO, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_LANGUAGE_TO, "")
        );

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_ID, "")) {
            ValidationErrors[RECORD_TRANSLATION_FIELD_VALUE_FROM].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
