#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"

class TRecordEnglishUser : public IRecord {
public:
    TRecordEnglishUser(const NJson::TJsonValue& json);

    bool IsValide(NJson::TJsonValue* error);
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
