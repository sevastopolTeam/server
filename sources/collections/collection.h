#pragma once

#include "contrib/json/json.h"
#include "library/mongo/wrappers.h"

#include "util/generic/vector.h"

template <class TRecord>
class ICollection {
public:
    ICollection(NMongo::THelper* master, const TString& dbName, const TString& collectionName)
        : Master(master)
        , DbName(dbName)
        , CollectionName(collectionName)
    {}

    bool Create(const TRecord& record);
    // TRecord FindById(const TString& recordId);

    ~ICollection() = default;

protected:
    NMongo::THelper* Master;
    TString DbName;
    TString CollectionName;
};

template <class TRecord>
bool ICollection<TRecord>::Create(const TRecord& record) {
    return Master->Insert(DbName, CollectionName, record.ToJson());
}

template <class TRecord>
TVector<TRecord> ICollection<TRecord>::Find() {
    TVector<NMongo::TBsonValue> result = Master->Find(DbName, CollectionName);
    TVector<TRecord> records;
    for (const auto& a : result) {
        records.push_back(TRecord(a.ToJson()));
    }
    return records;
}

// template <class TRecord>
// bool ICollection<TRecord>::Save(const TRecord& record) {
//     if (record.IsNewRecord()) {
//         Master->Insert(DbName, CollectionName, record);
//     } else {
//         // TODO
//     }
// }

// template <class TRecord>
// TRecord ICollection::FindById(const TString& recordId) {
//     return 
// }
