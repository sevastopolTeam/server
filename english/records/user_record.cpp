#include "user_record.h"
#include <ctime>
#include "contrib/json/json.h"

namespace {
    TString Normalize(const TString& str) {
        return NString::ToLower(str);
    }

    TString GenerateConfirmationKey() {
        std::time_t nowTime = std::time(0);
        return NString::ToString(nowTime) + '-' + NString::ToString(rand());
    }
}

namespace NEnglish {

    TRecordUser::TRecordUser(const NJson::TJsonValue& json)
        : Email(Normalize(json.value("Email", "")))
        , Name(json.value("Name", ""))
        , Phone(json.value("Phone", ""))
        , Password(json.value("Password", ""))
        , RepeatPassword(json.value("RepeatPassword", ""))
        , ConfirmationKey(GenerateConfirmationKey())
        , Confirmed(false)
        , ResetPasswordKey(GenerateConfirmationKey()) {}

    NJson::TJsonValue TRecordUser::ToJson() const {
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

    NJson::TJsonValue TRecordUser::GetUniqSelector() const {
        return { { "Email", Email } };
    }
}