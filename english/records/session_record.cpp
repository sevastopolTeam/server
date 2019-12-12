#include "session_record.h"
#include <ctime>
#include "contrib/json/json.h"

#include "contrib/md5/md5.h"

namespace {

    TString GenerateSessionToken() {
        std::time_t nowTime = time(NULL);
        return NString::ToString(nowTime) + '-' + NString::ToString(rand());
    }

}

namespace NEnglish {

    TRecordSession::TRecordSession(const NJson::TJsonValue& json)
        : UserId(json.value("UserId", ""))
        , Token(json.value("Token", "").size() ? json.value("Token", "") : GenerateSessionToken()) {}

    TRecordSession::TRecordSession(const TString& userId)
        : UserId(userId)
        , Token(GenerateSessionToken()) {}

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
