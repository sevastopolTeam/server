#include "user_record.h"

#include <ctime>

#include "contrib/json/json.h"
#include "contrib/md5/md5.h"

#include "util/generic/iostream.h"

namespace {

    TString Normalize(const TString& str) {
        return NString::ToLower(str);
    }

    TString GenerateRandomToken() {
        return md5(NString::ToString(rand())) + NString::ToString(time(NULL));
    }

    TString GeneratePasswordHash(const TString& password) {
        return md5(password); // TODO: add salt?
    }
}

namespace NEnglish {

    TString TRecordUser::GetId() const {
        return *(Id.Get());
    }

    bool TRecordUser::IsAdmin() const {
        return Role == USER_ROLE_ADMIN;
    }

    TRecordUser::TRecordUser(const NJson::TJsonValue& json)
        : Email(Normalize(json.value(RECORD_USER_FIELD_EMAIL, "")))
        , Name(json.value(RECORD_USER_FIELD_NAME, ""))
        , Phone(json.value(RECORD_USER_FIELD_PHONE, ""))
        , Password(json.value(RECORD_USER_FIELD_PASSWORD, ""))
        , RepeatPassword(json.value(RECORD_USER_FIELD_REPEAT_PASSWORD, ""))
        , ConfirmationKey(json.value(RECORD_USER_FIELD_CONFIRMATION_KEY, GenerateRandomToken()))
        , Confirmed(json.value(RECORD_USER_FIELD_CONFIRMED, false))
        , PasswordHash(json.value(RECORD_USER_FIELD_PASSWORD_HASH, GeneratePasswordHash(json.value(RECORD_USER_FIELD_PASSWORD, ""))))
        , ResetPasswordKey(json.value(RECORD_USER_FIELD_RESET_PASSWORD_KEY, GenerateRandomToken()))
        , Role(json.value(RECORD_USER_FIELD_ROLE, USER_ROLE_USER))
    {
        if (json.find("_id") != json.end()) {
            Id = json["_id"].value("$oid", "");
        } else {
            Id = Nothing();
        }
    }

    NJson::TJsonValue TRecordUser::ToJson() const {
        return {
            {RECORD_USER_FIELD_EMAIL, Email},
            {RECORD_USER_FIELD_NAME, Name},
            {RECORD_USER_FIELD_PHONE, Phone},
            {RECORD_USER_FIELD_PASSWORD_HASH, PasswordHash},
            {RECORD_USER_FIELD_CONFIRMATION_KEY, ConfirmationKey},
            {RECORD_USER_FIELD_CONFIRMED, Confirmed},
            {RECORD_USER_FIELD_RESET_PASSWORD_KEY, ResetPasswordKey},
            {RECORD_USER_FIELD_ROLE, Role}
        };
    }

    bool TRecordUser::CheckPassword(const TString& password) const {
        return PasswordHash == GeneratePasswordHash(password);
    }
}
