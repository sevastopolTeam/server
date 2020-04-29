#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

namespace {
    const TString VALIDATION_ERROR_REQUIRED = "CanNotBeEmpty";
    const TString VALIDATION_ERROR_EMAIL = "MustBeEmail";
    const TString VALIDATION_ERROR_SAME = "MustBeSame";
    const TString VALIDATION_ERROR_ALREADY_EXISTS = "AlreadyExists";
    const TString VALIDATION_ERROR_INCORRECT = "Incorrect";
    const TString VALIDATION_ERROR_NOT_FOUND = "NotFound";
    const TString VALIDATION_ERROR_MUST_BE_INT = "MustBeInt";
    const TString VALIDATION_ERROR_MUST_BE_LESS_THAN = "MustBeLessThan";
}

class IValidator {
public:
    IValidator() = default;
    IValidator(const NJson::TJsonValue& jsonData);
    NJson::TJsonValue GetValidationErrors() const;

protected:
    NJson::TJsonValue OriginJson;
    NJson::TJsonValue ValidationErrors;

    bool ValidateRequired(const TString& field);
    bool ValidateEmail(const TString& field);
    bool ValidateSame(const TString& validateField, const TString& sameField);
    bool ValidateUnsignedInt(const TString& validateField);
    bool ValidateLessThan(const TString& validateField);
};
