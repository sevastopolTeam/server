#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

class IValidator {
public:
    NJson::TJsonValue GetValidationErrors() const;

    void AddExternalValidation(const TString& field, const bool resolution, const TString& error);
    virtual bool Validate() = 0;

protected:
    NJson::TJsonValue OriginJson;
    NJson::TJsonValue ValidationErrors;
    bool IsValid;

    const TString VALIDATION_ERROR_REQUIRED = "CanNotBeEmpty";
    const TString VALIDATION_ERROR_EMAIL = "MustBeEmail";
    const TString VALIDATION_ERROR_SAME = "MustBeSame";

    bool ValidateRequired(const TString& field);
    bool ValidateEmail(const TString& field);
    bool ValidateSame(const TString& validateField, const TString& sameField);    
};
