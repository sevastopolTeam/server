#include "base_record.h"

#include "util/generic/ctype.h"

TRecordBase::TRecordBase(const NJson::TJsonValue& json) {
    Hello = NJson::GetString(json, "Hello", "");
}

NJson::TJsonValue TRecordBase::ForDB() const {
    NJson::TJsonValue json;
    json["Hello"] = Hello;
    return json;
}

NJson::TJsonValue TRecordBase::ToJson() const {
    return ForDB();
}
