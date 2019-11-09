#include "base.h"

TVector<NMongo::TBsonValue> TCollectionBase::Find() {
    return Master->Find(DbName, CollectionName);
}

bool TCollectionBase::Insert(const NMongo::TBsonValue& value) {
    return Master->Insert(DbName, CollectionName, value);
}
