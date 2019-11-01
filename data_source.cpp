#include "data_source.h"

TDataSource::TDataSource(const TString& uri, const TString& db, const TString& collection) {
    NMongo::Init();
    Master.reset(new NMongo::THelper(uri));
    mongoc_client_pool_new(mongoc_uri_new(uri.c_str()));
    Db = db;
    Collection = collection;
}

TDataSource::~TDataSource() {
    Master.reset();
    NMongo::Cleanup();
}

TVector<NMongo::TBsonValue> TDataSource::Find() {
    return Master->Find(Db, Collection);
}

bool TDataSource::Insert(NMongo::TBsonValue value) {
    return Master->Insert(Db, Collection, value);
}
