#include "validator_word_category.h"

#include "english/records/word_category_record.h"

namespace NEnglish {

    TValidatorWordCategory::TValidatorWordCategory(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorWordCategory::Validate(TDataSource& dataSource) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_WORD_CATEGORY_FIELD_NAME);
        isValid &= ValidateExists(dataSource);

        return static_cast<bool>(isValid);
    }

    bool TValidatorWordCategory::ValidateExists(TDataSource& dataSource) {
        const auto foundRecord = dataSource.English.CollectionWordCategory.FindByName(
            NJson::GetString(OriginJson, RECORD_WORD_CATEGORY_FIELD_NAME, "")
        );

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_FIELD_ID, "")) {
            ValidationErrors[RECORD_WORD_CATEGORY_FIELD_NAME].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}
