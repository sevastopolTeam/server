#include "validator.h"

NJson::TJsonValue IValidator::GetValidationErrors() const {
    return ValidationErrors;
}

bool IValidator::ValidateRequired(const TString& field) {
    bool valid = OriginJson.value(field, "").size();
    if (!valid) {
        ValidationErrors[field].push_back(VALIDATION_ERROR_REQUIRED);
        IsValid = false;
    }
    return valid;
}

bool IValidator::ValidateEmail(const TString& field) {
    bool valid = NString::Contains(OriginJson.value(field, ""), '@');
    if (!valid) {
        ValidationErrors[field].push_back(VALIDATION_ERROR_EMAIL);
        IsValid = false;
    }
    return valid;
}

bool IValidator::ValidateSame(const TString& validateField, const TString& sameField) {
    bool valid = OriginJson.value(validateField, "") == OriginJson.value(sameField, "");

    if (!valid) {
        ValidationErrors[validateField].push_back(VALIDATION_ERROR_SAME);
        IsValid = false;
    }
    return valid;
}