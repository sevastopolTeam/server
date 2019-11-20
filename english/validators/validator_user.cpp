#include "validator_user.h"

namespace NEnglish {

	TValidatorUser::TValidatorUser(const NJson::TJsonValue& jsonData) {
		// OriginJson = jsonData;
		IsValid = false;
	}

	// bool TValidatorUser::Validate() const {
	// 	// IsValid = true;
	// 	// ValidateField("Name", { VALIDATION_REQUIRED });
	// 	// ValidateField("Email", { VALIDATION_REQUIRED, VALIDATION_EMAIL });

	// 	return IsValid;
	// }

}