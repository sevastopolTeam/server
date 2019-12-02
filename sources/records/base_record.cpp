#include "base_record.h"

TRecordBase::TRecordBase(const NJson::TJsonValue& json) {
    Hello = json.value("Hello", "");
}

NJson::TJsonValue TRecordBase::ToJson() const {
    NJson::TJsonValue json;
    json["Hello"] = Hello;
    return json;
}
