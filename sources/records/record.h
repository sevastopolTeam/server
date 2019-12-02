#pragma once

#include "contrib/json/json.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

class IRecord {
public:
    virtual NJson::TJsonValue ToJson() const = 0;

    bool IsNewRecord() const;

    TString GetId() {
        return Id;
    }
protected:
    bool NewRecord = false;
    TString Id;
};
