#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"

namespace NEnglish {

    class TRecordUser : public IRecord {
    public:
        TRecordUser(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;

        NJson::TJsonValue GetUniqSelector() const;

    private:
        // DB fields
        TString Email;
        TString Name;
        TString Phone;
        TString PasswordHash;
        TString ConfirmationKey;
        bool Confirmed;
        TString ResetPasswordKey;

        // extra fields
        TString Password;
        TString RepeatPassword;
    };

}