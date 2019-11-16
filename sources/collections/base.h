#pragma once

#include "collection.h"
#include "sources/records/base_record.h"

class TCollectionBase : public ICollection {
public:
    using ICollection::ICollection;

    TVector<TRecordBase> Find();
    bool Insert(const TRecordBase& value);
};
