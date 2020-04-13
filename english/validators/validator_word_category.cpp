#include "validator_word_category.h"

#include "english/records/word_category_record.h"

namespace NEnglish {

    TValidatorWordCategory::TValidatorWordCategory(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorWordCategory::Validate(TDataSource& dataSource) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_WORD_CATEGORY_FIELD_NAME);

        return static_cast<bool>(isValid);
    }
}
