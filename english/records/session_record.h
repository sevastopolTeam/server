#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"

namespace NEnglish {

    const TString RECORD_SESSION_FIELD_USER_ID = "UserId";
    const TString RECORD_SESSION_FIELD_TOKEN = "Token";

    class TRecordSession : public IRecord {
    public:
        TRecordSession() = default;
        TRecordSession(const NJson::TJsonValue& json);
        TRecordSession(const TString& userId);

        NJson::TJsonValue ToJson() const override;

        TString GetUserId() const;
        TString GetToken() const;
    private:
        // DB fields
        TString UserId;
        TString Token;
    };
}
