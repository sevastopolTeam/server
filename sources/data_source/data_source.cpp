#include "data_source.h"

#include "util/generic/iostream.h"

namespace {
    const TString COLLECTION_NAME_BASE = "base";
}

TDataSource::TDataSource(const TString& uri, const TString& dbName)
    : Master(new NMongo::THelper(uri))
    , English(Master.get(), dbName)
    , CollectionBase(Master.get(), dbName, COLLECTION_NAME_BASE)
{
    INFO_LOG << "Started mongoDB" << Endl;
}

TDataSource::~TDataSource() {
    INFO_LOG << "Stopped mongoDB" << Endl;
}
