#pragma once

#include "record.h"

class TRecordBase : public IRecord {
public:
    TRecordBase(const NJson::TJsonValue& json);

    NJson::TJsonValue ToJson() const override;
    NJson::TJsonValue ForDB() const override;

private:
    TString Hello;
};
