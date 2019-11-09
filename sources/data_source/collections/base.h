#pragma once

#include "collection.h"
#include "library/mongo/wrappers.h"

class TCollectionBase : public ICollection {
public:
    using ICollection::ICollection;

    TVector<NMongo::TBsonValue> Find();
    bool Insert(const NMongo::TBsonValue& value);
};
