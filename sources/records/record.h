#pragma once

#include "contrib/json/json.h"
#include "util/generic/maybe.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

class IRecord {
public:
	IRecord() = default;
	IRecord(const TMaybe<TString>& id);
    virtual NJson::TJsonValue ToJson() const = 0;
    TString GetId() const;
protected:
    TMaybe<TString> Id;
};
