#include "data_source.h"

#include <iostream>

namespace {
    const TString COLLECTION_BASE_NAME = "base";
}

TDataSource::TDataSource(const TString& uri, const TString& dbName)
    : Master(new NMongo::THelper(uri))
    , Base(Master.get(), dbName, COLLECTION_BASE_NAME)
{
    std::cout << "Started mongoDB" << std::endl;
}

TDataSource::~TDataSource() {
    std::cout << "Stopped mongoDB" << std::endl;
}
