#include "user_record.h"

#include <ctime>
#include <iostream>

namespace {
    TString Normalize(const TString& str) {
        return str;
    }

    TString GenerateConfirmationKey() {
        std::time_t nowTime = std::time(0);
        return NString::ToString(nowTime) + '-' + NString::ToString(rand());
    }
}

TRecordEnglishUser::TRecordEnglishUser(const NJson::TJsonValue& json)
    : Email(Normalize(json.value("Email", "")))
    , Name(json.value("Name", ""))
    , Phone(json.value("Phone", ""))
    , Password(json.value("Password", ""))
    , RepeatPassword(json.value("RepeatPassword", ""))
    , ConfirmationKey(GenerateConfirmationKey())
    , Confirmed(false)
    , ResetPasswordKey(GenerateConfirmationKey())
{}

bool TRecordEnglishUser::IsValide(NJson::TJsonValue* error) {
    if (Password != RepeatPassword) {
        (*error)["status"] = "validation_error";
        (*error)["validation_errors"] = { { "Password", "is not same" } };
        return false;
    }
    (*error)["status"] = "ok";
    return true;
}

NJson::TJsonValue TRecordEnglishUser::ToJson() const {
    return {
        {"Email", Email},
        {"Name", Name},
        {"Phone", Phone},
        {"Password", Password},
        {"ConfirmationKey", ConfirmationKey},
        {"Confirmed", Confirmed},
        {"ResetPasswordKey", ResetPasswordKey}
    };
}

NJson::TJsonValue TRecordEnglishUser::GetUniqSelector() const {
    return { { "Email", Email } };
}
