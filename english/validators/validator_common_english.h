#pragma once

#include "util/generic/string.h"

#include "sources/validators/validator.h"

namespace NEnglish {

    const TString VALIDATION_ERROR_PHONE = "MustBePhone";

    class IValidatorCommonEnglish : public IValidator {
    public:
    	IValidatorCommonEnglish(const NJson::TJsonValue& jsonData);
    protected:
        bool ValidatePhone(const TString& field);
    };
}
