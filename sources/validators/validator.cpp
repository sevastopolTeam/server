#include "validator.h"

NJson::TJsonValue IValidator::GetValidationErrors() const {
    return ValidationErrors;
}

bool IValidator::ValidateRequired(const TString& field) {
    if (OriginJson.value(field, "").empty()) {
        ValidationErrors[field].push_back(VALIDATION_ERROR_REQUIRED);
        return false;
    }

    return true;
}

bool IValidator::ValidateEmail(const TString& field) {
    if (!NString::Contains(OriginJson.value(field, ""), '@')) {
        ValidationErrors[field].push_back(VALIDATION_ERROR_EMAIL);
        return false;
    }

    return true;
}

bool IValidator::ValidateSame(const TString& validateField, const TString& sameField) {
    if (OriginJson.value(validateField, "") != OriginJson.value(sameField, "")) {
        ValidationErrors[validateField].push_back(VALIDATION_ERROR_SAME);
        return false;
    }

    return true;
}
