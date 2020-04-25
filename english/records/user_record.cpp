#include "user_record.h"

#include <ctime>

#include "contrib/json/json.h"

#include "util/generic/iostream.h"
#include "util/generic/hash_functions.h"
#include "util/generic/ctype.h"

namespace {
    TString Normalize(const TString& str) {
        return NString::ToLower(str);
    }
}

namespace NEnglish {

    bool TRecordUser::IsAdmin() const {
        return Role == USER_ROLE_ADMIN;
    }

    TRecordUser::TRecordUser(const NJson::TJsonValue& json)
        : Email(Normalize(NJson::GetString(json, RECORD_USER_FIELD_EMAIL, "")))
        , Name(NJson::GetString(json, RECORD_USER_FIELD_NAME, ""))
        , Phone(NJson::GetString(json, RECORD_USER_FIELD_PHONE, ""))
        , Password(NJson::GetString(json, RECORD_USER_FIELD_PASSWORD, ""))
        , RepeatPassword(NJson::GetString(json, RECORD_USER_FIELD_REPEAT_PASSWORD, ""))
        , ConfirmationKey(NJson::GetString(json, RECORD_USER_FIELD_CONFIRMATION_KEY, NHashFunctions::GenerateRandomToken()))
        , Confirmed(NJson::GetBool(json, RECORD_USER_FIELD_CONFIRMED, false))
        , PasswordHash(NJson::GetString(json, RECORD_USER_FIELD_PASSWORD_HASH, NHashFunctions::GeneratePasswordHash(json.value(RECORD_USER_FIELD_PASSWORD, ""))))
        , ResetPasswordKey(NJson::GetString(json, RECORD_USER_FIELD_RESET_PASSWORD_KEY, NHashFunctions::GenerateRandomToken()))
        , Role(NJson::GetString(json, RECORD_USER_FIELD_ROLE, USER_ROLE_USER))
        , IRecord(NJson::GetString(json, PATH_TO_RECORD_ID)) {}

    NJson::TJsonValue TRecordUser::ForDB() const {
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

    NJson::TJsonValue TRecordUser::ToJson() const {
        NJson::TJsonValue json = ForDB();
        if (Id.has_value()) {
            json[RECORD_FIELD_ID] = *Id;
        }
        return json;
    }

    bool TRecordUser::CheckPassword(const TString& password) const {
        return PasswordHash == NHashFunctions::GeneratePasswordHash(password);
    }
}
