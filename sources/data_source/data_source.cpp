#include "data_source.h"

#include <iostream>

TDataSource::TDataSource(const TString& uri, const TString& db, const TString& collection) {
    NMongo::Init();
    Master.reset(new NMongo::THelper(uri));
    Db = db;
    Collection = collection;
    std::cout << "Started mongoDB" << std::endl;
}

TDataSource::~TDataSource() {
    NMongo::Cleanup();
    std::cout << "Stopped mongoDB" << std::endl;
}

TVector<NMongo::TBsonValue> TDataSource::Find() {
    return Master->Find(Db, Collection);
}

bool TDataSource::Insert(NMongo::TBsonValue value) {
    return Master->Insert(Db, Collection, value);
}
