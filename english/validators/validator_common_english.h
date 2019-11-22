#pragma once

#include "util/generic/string.h"

#include "sources/validators/validator.h"

namespace NEnglish {

    class IValidatorCommonEnglish : public IValidator {
    public:
        virtual bool Validate() = 0;

    protected:
        const TString VALIDATION_ERROR_PHONE = "MustBePhone";

        bool ValidatePhone(const TString& field);
    };
}
