#pragma once

#include "util/generic/string.h"

#include "sources/validators/validator.h"

namespace NEnglish {

    const TString VALIDATION_ERROR_PHONE = "MustBePhone";

    class IValidatorCommonEnglish : public IValidator {
    public:
        virtual bool Validate() = 0;

    protected:
        bool ValidatePhone(const TString& field);
    };
}
