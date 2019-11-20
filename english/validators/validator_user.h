#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

// #include "sources/validators/validator.h"

namespace NEnglish {

	class TValidatorUser {
	public:
		TValidatorUser(const NJson::TJsonValue& jsonData);

		// bool Validate() const override;
	private:
		bool IsValid;
	};

}