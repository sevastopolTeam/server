#include "validator.h"

// virtual bool IValidator::ValidateRequired(const TString& field) {
// 	bool valid = OriginJson.value(field, "").size();
// 	if (!valid) {
// 		ValidationErrors[field] = VALIDATION_ERROR_REQUIRED;
// 		IsValid = false;
// 	}
// 	return valid;
// }

// virtual bool IValidator::ValidateEmail(const TString& field) {
// 	bool valid = NString::Contains(OriginJson.value(field, ""), '@');
// 	if (!valid) {
// 		ValidationErrors[field] = VALIDATION_ERROR_EMAIL;
// 		IsValid = false;
// 	}
// 	return valid;
// }

// virtual bool IValidator::ValidateSame(const TVector<TString>& fields) {
// 	bool valid = true;

// 	for (int i = 1; i < fields.size(); ++i) {
// 		if (OriginJson.value(fields[i], "") == OriginJson.value(fields[0], "")) {
// 			valid = false;
// 			break;
// 		}
// 	}
	
// 	if (!valid) {
// 		ValidationErrors[field1] = VALIDATION_ERROR_SAME;
// 		IsValid = false;
// 	}
// 	return valid;
// }

// virtual bool IValidator::ValidateField(const TString& field, const TVector<TString>& validations) {
// 	bool valid = true;
// 	for (auto validation: validations) {
// 		switch(validation) {
// 			case VALIDATION_REQUIRED: {
// 				if (!ValidateRequired(field)) {
// 					valid = false;
// 				}
// 				break;
// 			}
// 			case VALIDATION_EMAIL: {
// 				if (!ValidateRequired(field)) {
// 					valid = false;
// 				}
// 				break;
// 			}
// 		}
// 	}
// 	if (!valid) {
// 		IsValid = false;
// 	}
// 	return valid;
// }

// virtual bool IValidator::ValidateFields(const TVector<TString>& fields, const TVector<TString>& validations) {
// 	bool valid = true;
// 	for (auto validation: validations) {
// 		switch(validation) {
// 			case VALIDATION_SAME: {
// 				if (!ValidateSame(fields)) {
// 					valid = false;
// 				}
// 				break;
// 			}
// 		}
// 	}
// 	if (!valid) {
// 		IsValid = false;
// 	}
// 	return valid;
// }
