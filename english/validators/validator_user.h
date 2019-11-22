#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

#include "sources/validators/validator.h"

namespace NEnglish {

	class TValidatorUser : public IValidator {
	public:
		TValidatorUser(const NJson::TJsonValue& jsonData);
		bool Validate() override;

	private:
		bool ValidatePhone(const TString& field);

		const TString VALIDATION_ERROR_PHONE = "must_be_phone";
	};

}