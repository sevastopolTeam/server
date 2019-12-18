#include "session_record.h"
#include <ctime>
#include "contrib/json/json.h"

#include "util/generic/hash_functions.h"

namespace NEnglish {

    TRecordSession::TRecordSession(const NJson::TJsonValue& json)
        : UserId(json.value(RECORD_SESSION_FIELD_USER_ID, ""))
        , Token(json.value(RECORD_SESSION_FIELD_TOKEN, NHashFunctions::GenerateRandomToken())) {}

    TRecordSession::TRecordSession(const TString& userId)
        : UserId(userId)
        , Token(NHashFunctions::GenerateRandomToken()) {}

    TString TRecordSession::GetUserId() const {
        return UserId;
    }

    TString TRecordSession::GetToken() const {
        return Token;
    }

    NJson::TJsonValue TRecordSession::ToJson() const {
        return {
            {RECORD_SESSION_FIELD_USER_ID, UserId},
            {RECORD_SESSION_FIELD_TOKEN, Token}
        };
    }
}
