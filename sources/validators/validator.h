#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

class IValidator {
public:
 //    virtual bool ValidateRequired(const TString& field);
 //    virtual bool ValidateEmail(const TString& field);
	// virtual bool ValidateSame(const TString& field1, const TString& field2);
	// virtual bool ValidateField(const TString& field, const TVector<TString>& validations);
	// virtual bool ValidateFields(const TVector<TString>& fields, const TVector<TString>& validations);

	// virtual bool Validate() const = 0;
// protected:
// 	NJson::TJsonValue OriginJson;
// 	NJson::TJsonValue ValidationErrors;
// 	bool IsValid;

// 	const TString VALIDATION_REQUIRED = "required";
// 	const TString VALIDATION_EMAIL = "email";
// 	const TString VALIDATION_SAME = "same";

// 	const TString VALIDATION_ERROR_REQUIRED = "can_not_be_empty";
// 	const TString VALIDATION_ERROR_EMAIL = "must_be_email";
// 	const TString VALIDATION_ERROR_SAME = "must_be_same";
};
