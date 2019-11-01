#pragma once

#include "library/mongo/wrappers.h"

class TDataSource {
public:
    TDataSource(const TString& uri, const TString& db, const TString& collection);
    ~TDataSource();

    TVector<NMongo::TBsonValue> Find();
    bool Insert(NMongo::TBsonValue value);

private:
    std::unique_ptr<NMongo::THelper> Master;
    TString Db;
    TString Collection;
};
