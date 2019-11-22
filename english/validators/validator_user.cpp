#include "validator_user.h"

#include "util/generic/iostream.h"

namespace NEnglish {

	TValidatorUser::TValidatorUser(const NJson::TJsonValue& jsonData) {
		OriginJson = jsonData;
		IsValid = false;
	}

	bool TValidatorUser::Validate() {
		IsValid = true;
		ValidateRequired("Name");

		ValidateRequired("Email");
		ValidateEmail("Email");

		ValidateRequired("Phone");
		ValidatePhone("Phone");

		ValidateRequired("Password");

		ValidateSame("RepeatPassword", "Password");

		return IsValid;
	}

	bool TValidatorUser::ValidatePhone(const TString& field) {
		bool valid = true;
		const TString& phone = OriginJson.value(field, "");
		
		if (phone.size() > 2 && phone[0] == '+') {
			for (size_t i = 1; i < phone.size(); ++i) {
				if (!NString::IsDigit(phone[i])) {
					valid = false;
				}
			}
		} else {
			valid = false;
		}
		if (!valid) {
			ValidationErrors[field].push_back(VALIDATION_ERROR_PHONE);
			IsValid = false;
		}
		return valid;
	}

}