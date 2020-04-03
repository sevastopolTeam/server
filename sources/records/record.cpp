#include "record.h"

TString IRecord::GetId() const {
    return *Id;
}

IRecord::IRecord(const TMaybe<TString>& id): Id(id) {}