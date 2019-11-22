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

}