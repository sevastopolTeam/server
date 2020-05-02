#include "record.h"

TString IRecord::GetId() const {
    return Id.value();
}

IRecord::IRecord(const TMaybe<TString>& id): Id(id) {}
