#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"

namespace NEnglish {

    class TRecordUser : public IRecord {
    public:
        TRecordUser(const NJson::TJsonValue& json);

        bool IsValid(NJson::TJsonValue* error);
        NJson::TJsonValue ToJson() const override;

        NJson::TJsonValue GetUniqSelector() const;

    private:
        TString Email;
        TString Name;
        TString Phone;
        TString Password;
        TString RepeatPassword;
        TString ConfirmationKey;
        bool Confirmed;
        TString ResetPasswordKey;
    };

}