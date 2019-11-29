#include "base.h"
#include "library/mongo/wrappers.h"
#include <iostream>

TVector<TRecordBase> TCollectionBase::Find() {
    TVector<NMongo::TBsonValue> result = Master->Find(DbName, CollectionName);
    TVector<TRecordBase> records;
    for (const auto& a : result) {
        records.push_back(TRecordBase(a.ToJson()));
    }
    return records;
}

bool TCollectionBase::Insert(const TRecordBase& value) {
    return Master->Insert(DbName, CollectionName, NMongo::TBsonValue(value.ToJson()));
}
