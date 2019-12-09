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


    bool Exists(const NJson::TJsonValue& selection);
    bool Create(const TRecord& record);
    TVector<TRecord> Find(const NJson::TJsonValue& selection = NJson::TJsonValue());
    TMaybe<TRecord> FindBy(const NJson::TJsonValue& selection);
    TMaybe<TRecord> FindById(const TString& recordId);

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
TVector<TRecord> ICollection<TRecord>::Find(const NJson::TJsonValue& selection) {
    TVector<NMongo::TBsonValue> result = Master->Find(DbName, CollectionName);
    TVector<TRecord> records;
    for (const auto& a : result) {
        records.push_back(TRecord(a.ToJson()));
    }
    return records;
}

template <class TRecord>
TMaybe<TRecord> ICollection<TRecord>::FindBy(const NJson::TJsonValue& selection) {
    TVector<NMongo::TBsonValue> result = Master->Find(
        DbName,
        CollectionName,
        selection,
        /* skip */ 0,
        /* limit */ 1
    );
    if (result.empty()) {
        return Nothing();
    }

    return TRecord(result[0].ToJson());
}

template <class TRecord>
bool ICollection<TRecord>::Exists(const NJson::TJsonValue& selection) {
    return Master->Find(DbName, CollectionName, selection,/* skip */ 0,/* limit */ 1).size();
}

template <class TRecord>
TMaybe<TRecord> ICollection<TRecord>::FindById(const TString& recordId) {
    NJson::TJsonValue json;
    json["_id"]["$oid"] = recordId;
    TVector<NMongo::TBsonValue> result = Master->Find(
        DbName,
        CollectionName,
        json,
        /* skip */ 0,
        /* limit */ 1
    );
    if (result.empty()) {
        return Nothing();
    }

    return TRecord(result[0].ToJson());
}
