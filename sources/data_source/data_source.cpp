#include "data_source.h"

#include <iostream>

namespace {
    const TString COLLECTION_NAME_BASE = "base";
}

namespace NEnglish {
    const TString COLLECTION_NAME_USER = "english_user";
}

TEnglishCollections::TEnglishCollections(const NEnglish::TCollectionUser& collectionUser)
	: CollectionUser(collectionUser) {}

TDataSource::TDataSource(const TString& uri, const TString& dbName)
    : Master(new NMongo::THelper(uri))
    , CollectionBase(Master.get(), dbName, COLLECTION_NAME_BASE)
    , English(
    	NEnglish::TCollectionUser(Master.get(), dbName, NEnglish::COLLECTION_NAME_USER)
    )
{
    std::cout << "Started mongoDB" << std::endl;
}

TDataSource::~TDataSource() {
    std::cout << "Stopped mongoDB" << std::endl;
}
