#pragma once

#include "library/mongo/wrappers.h"

class ICollection {
public:
    ICollection(NMongo::THelper* master, const TString& dbName, const TString& collectionName)
        : Master(master)
        , DbName(dbName)
        , CollectionName(collectionName)
    {}

    ~ICollection() = default;

protected:
    NMongo::THelper* Master;
    TString DbName;
    TString CollectionName;
};
