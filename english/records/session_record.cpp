#include "session_record.h"
#include <ctime>
#include "contrib/json/json.h"

#include "contrib/md5/md5.h"

namespace {

    TString GenerateRandomToken() {
        std::time_t nowTime = time(NULL);
        return md5(NString::ToString(rand())) + NString::ToString(nowTime);
    }

}

namespace NEnglish {

    TRecordSession::TRecordSession(const NJson::TJsonValue& json)
        : UserId(json.value(RECORD_SESSION_FIELD_USER_ID, ""))
        , Token(json.value(RECORD_SESSION_FIELD_TOKEN, GenerateRandomToken())) {}

    TRecordSession::TRecordSession(const TString& userId)
        : UserId(userId)
        , Token(GenerateRandomToken()) {}

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
