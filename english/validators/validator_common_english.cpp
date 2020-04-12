#include "validator_common_english.h"

#include "util/generic/ctype.h"

namespace NEnglish {
    IValidatorCommonEnglish::IValidatorCommonEnglish(const NJson::TJsonValue& jsonData): IValidator(jsonData) {}

    bool IValidatorCommonEnglish::ValidatePhone(const TString& field) {
        bool valid = true;
        const TString& phone = NJson::GetString(OriginJson, field, "");
        
        if (phone.size() > 2 && phone.front() == '+') {
            for (size_t i = 1; i < phone.size(); ++i) {
                if (!NType::IsDigit(phone[i])) {
                    valid = false;
                }
            }
        } else {
            valid = false;
        }
        if (!valid) {
            ValidationErrors[field].push_back(VALIDATION_ERROR_PHONE);
            return false;
        }

        return true;
    }
}
