#pragma once

#include "contrib/json/json.h"

#include "library/mongo/wrappers.h"

template <class TRecord>
class ICollection {
public:
    ICollection(NMongo::THelper* master, const TString& dbName, const TString& collectionName)
        : Master(master)
        , DbName(dbName)
        , CollectionName(collectionName)
    {}

    // bool Create(const TRecord& record);
    // bool Save(const TRecord& record);
    int Test();
    // TRecord FindById(const TString& recordId);

    ~ICollection() = default;

protected:
    NMongo::THelper* Master;
    TString DbName;
    TString CollectionName;
};

// template <class TRecord>
// int ICollection<TRecord>::Test() {
//     return 5;
// }