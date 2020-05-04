#pragma once

#include "contrib/json/json.h"
#include "util/generic/maybe.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

const TString PATH_TO_RECORD_ID = "_id.$oid";
const TString RECORD_FIELD_ID = "Id";

class IRecord {
public:
	IRecord() = default;
	IRecord(const TMaybe<TString>& id);
    virtual NJson::TJsonValue ForDB() const = 0;
    virtual NJson::TJsonValue ToJson() const = 0;
    TString GetId() const;
protected:
    TMaybe<TString> Id;
};
