#pragma once

#include "record.h"
#include "contrib/json/json.h"
#include "util/generic/string.h"

class TRecordBase : public IRecord {
public:
    TRecordBase(const NJson::TJsonValue& json);

    NJson::TJsonValue ToJson() const override;

private:
    TString Hello;
};
