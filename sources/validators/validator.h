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
}

class IValidator {
public:
    NJson::TJsonValue GetValidationErrors() const;

protected:
    NJson::TJsonValue OriginJson;
    NJson::TJsonValue ValidationErrors;
    bool IsValid;

    void ValidateRequired(const TString& field);
    void ValidateEmail(const TString& field);
    void ValidateSame(const TString& validateField, const TString& sameField); 
};
