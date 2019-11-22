#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

class IValidator {
public:
    NJson::TJsonValue GetValidationErrors() const;

    void AddValidationError(const TString& field, const TString& error);
	virtual bool Validate() = 0;
protected:
	NJson::TJsonValue OriginJson;
	NJson::TJsonValue ValidationErrors;
	bool IsValid;

	const TString VALIDATION_ERROR_REQUIRED = "can_not_be_empty";
	const TString VALIDATION_ERROR_EMAIL = "must_be_email";
	const TString VALIDATION_ERROR_SAME = "must_be_same";

	bool ValidateRequired(const TString& field);
    bool ValidateEmail(const TString& field);
	bool ValidateSame(const TString& validateField, const TString& sameField);
	
};
