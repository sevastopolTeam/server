#pragma once

#include "collection.h"
#include "sources/records/base_record.h"

class TCollectionBase : public ICollection<TRecordBase> {
public:
    using ICollection::ICollection;
};
