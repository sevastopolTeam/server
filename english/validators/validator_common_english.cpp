#include "validator_common_english.h"

#include "util/generic/ctype.h"

namespace NEnglish {

    bool IValidatorCommonEnglish::ValidatePhone(const TString& field) {
        bool valid = true;
        const TString& phone = OriginJson.value(field, "");
        
        if (phone.size() > 2 && phone[0] == '+') {
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
