#pragma once

#include "contrib/json/json.h"

class IRecord {
public:
    virtual NJson::TJsonValue ToJson() const = 0;
};
