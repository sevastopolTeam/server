#pragma once

#include "record.h"

class TRecordBase : public IRecord {
public:
    TRecordBase(const NJson::TJsonValue& json);

    NJson::TJsonValue ToJson() const override;

private:
    TString Hello;
};
