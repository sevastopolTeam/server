#pragma once

#include "util/generic/string.h"

#include "sources/validators/validator.h"

namespace NEnglish {

    const TString VALIDATION_ERROR_PHONE = "MustBePhone";

    class IValidatorCommonEnglish : public IValidator {
    protected:
        void ValidatePhone(const TString& field);
    };
}
