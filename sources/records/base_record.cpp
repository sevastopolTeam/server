#include "base_record.h"

TRecordBase::TRecordBase(const NJson::TJsonValue& json) {
    Hello = json["hello"].get<TString>();
}

NJson::TJsonValue TRecordBase::ToJson() const {
    NJson::TJsonValue json;
    json["hello"] = Hello;
    return json;
}
