#include "user_record.h"

#include <ctime>

#include "contrib/json/json.h"
#include "contrib/md5/md5.h"

namespace {

    TString Normalize(const TString& str) {
        return NString::ToLower(str);
    }

    TString GenerateConfirmationKey() {
        std::time_t nowTime = time(NULL);
        return NString::ToString(nowTime) + '-' + NString::ToString(rand());
    }

    TString GeneratePasswordHash(const TString& password) {
        return md5(password); // TODO: add salt?
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
        , ResetPasswordKey(GenerateConfirmationKey())
        , PasswordHash(GeneratePasswordHash(json.value("Password", ""))) {}

    NJson::TJsonValue TRecordUser::ToJson() const {
        return {
            {"Email", Email},
            {"Name", Name},
            {"Phone", Phone},
            {"ConfirmationKey", ConfirmationKey},
            {"Confirmed", Confirmed},
            {"ResetPasswordKey", ResetPasswordKey},
            {"PasswordHash", PasswordHash}
        };
    }
}