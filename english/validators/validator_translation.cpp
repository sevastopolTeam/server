#include "validator_translation.h"

#include "english/records/translation_record.h"

namespace NEnglish {

    TValidatorTranslation::TValidatorTranslation(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
    }

    bool TValidatorTranslation::Validate(TDataSource& dataSource) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_VALUE_FROM);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_VALUE_TO);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_LANGUAGE_FROM);
        isValid &= ValidateRequired(RECORD_TRANSLATION_FIELD_LANGUAGE_TO);

        isValid &= ValidateExists(dataSource);
        return (bool)isValid;
    }

    bool TValidatorTranslation::ValidateExists(TDataSource& dataSource) {
        bool valid = !dataSource.English.CollectionTranslation.ExistsByFullMatching(
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_VALUE_FROM, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_VALUE_TO, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_FIELD_LANGUAGE_TO, "")
        );
        if (!valid) {
            ValidationErrors[RECORD_TRANSLATION_FIELD_VALUE_FROM].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
