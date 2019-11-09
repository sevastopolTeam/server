#include "data_source.h"

#include <iostream>

namespace {
    const TString COLLECTION_NAME_BASE = "base";
    const TString COLLECTION_NAME_USER = "user";
}

TDataSource::TDataSource(const TString& uri, const TString& dbName)
    : Master(new NMongo::THelper(uri))
    , Base(Master.get(), dbName, COLLECTION_NAME_BASE)
    , User(Master.get(), dbName, COLLECTION_NAME_USER)
{
    std::cout << "Started mongoDB" << std::endl;
}

TDataSource::~TDataSource() {
    std::cout << "Stopped mongoDB" << std::endl;
}
