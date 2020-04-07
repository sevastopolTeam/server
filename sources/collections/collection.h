#pragma once

#include <limits>

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
    TVector<TRecord> Find(
        const NJson::TJsonValue& selection = NJson::TJsonValue::object(),
        const int skipRecords = 0,
        const int limitRecords = std::numeric_limits<int>::max()
    );
    TRecord FindAndModify(
        const NJson::TJsonValue& selection,
        const NJson::TJsonValue& update
    );
    TRecord FindByIdAndModify(
        const TString& recordId,
        const TRecord& updateRecord
    );
    TVector<TRecord> All();
    TMaybe<TRecord> FindFirst(const NJson::TJsonValue& selection);
    TMaybe<TRecord> FindById(const TString& recordId);
    bool Remove(const NJson::TJsonValue& selection);
    bool RemoveById(const TString& recordId);

    bool CreateIndex(const TString& index, bool uniq = false, bool desc = false, int expireAfterSeconds = -1);

    ~ICollection() = default;

protected:
    NMongo::THelper* Master;
    TString DbName;
    TString CollectionName;
};

template <class TRecord>
bool ICollection<TRecord>::Create(const TRecord& record) {
    return Master->Insert(DbName, CollectionName, record.ForDB());
}

template <class TRecord>
TVector<TRecord> ICollection<TRecord>::Find(const NJson::TJsonValue& selection, const int skipRecords, const int limitRecords) {
    TVector<NMongo::TBsonValue> result = Master->Find(
        DbName,
        CollectionName,
        selection,
        skipRecords,
        limitRecords
    );
    TVector<TRecord> records;
    for (const auto& a : result) {
        records.push_back(TRecord(a.ToJson()));
    }
    return records;
}

template <class TRecord>
TRecord ICollection<TRecord>::FindAndModify(const NJson::TJsonValue& selection, const NJson::TJsonValue& update) {
    NMongo::TBsonValue result = Master->FindAndModify(
        DbName,
        CollectionName,
        selection,
        update
    );
    return TRecord(result.ToJson());
}

template <class TRecord>
TRecord ICollection<TRecord>::FindByIdAndModify(const TString& recordId, const TRecord& updateRecord) {
    NJson::TJsonValue json;
    json["_id"]["$oid"] = recordId;
    return FindAndModify(json, updateRecord.ForDB());
}

template <class TRecord>
TVector<TRecord> ICollection<TRecord>::All() {
    return Find();
}

template <class TRecord>
TMaybe<TRecord> ICollection<TRecord>::FindFirst(const NJson::TJsonValue& selection) {
    TVector<TRecord> records = Find(selection,/* skip */ 0,/* limit */ 1);
    if (records.empty()) {
        return Nothing();
    }
    return records[0];
}

template <class TRecord>
bool ICollection<TRecord>::Remove(const NJson::TJsonValue& selection) {
    return Master->Remove(DbName, CollectionName, selection);
}

template <class TRecord>
bool ICollection<TRecord>::RemoveById(const TString& recordId) {
    NJson::TJsonValue json;
    json["_id"]["$oid"] = recordId;
    return Remove(json);
}

template <class TRecord>
bool ICollection<TRecord>::Exists(const NJson::TJsonValue& selection) {
    return Find(selection,/* skip */ 0,/* limit */ 1).size();
}

template <class TRecord>
TMaybe<TRecord> ICollection<TRecord>::FindById(const TString& recordId) {
    NJson::TJsonValue json;
    json["_id"]["$oid"] = recordId;
    return FindFirst(json);
}

template <class TRecord>
bool ICollection<TRecord>::CreateIndex(const TString& index, bool uniq, bool desc, int expireAfterSeconds) {
    return Master->CreateIndex(DbName, CollectionName, index, uniq, desc, expireAfterSeconds);
}
