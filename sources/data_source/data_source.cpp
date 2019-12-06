#include "data_source.h"

#include "util/generic/iostream.h"

namespace {
    const TString COLLECTION_NAME_BASE = "base";
}

namespace NEnglish {
    const TString COLLECTION_NAME_USER = "english_user";
    const TString COLLECTION_NAME_SESSION = "english_session";
}

TEnglishCollections::TEnglishCollections(
    const NEnglish::TCollectionUser& collectionUser,
    const NEnglish::TCollectionSession& collectionSession
    )
    : CollectionUser(collectionUser)
    , CollectionSession(collectionSession) {}

TDataSource::TDataSource(const TString& uri, const TString& dbName)
    : Master(new NMongo::THelper(uri))
    , English(
        NEnglish::TCollectionUser(Master.get(), dbName, NEnglish::COLLECTION_NAME_USER),
        NEnglish::TCollectionSession(Master.get(), dbName, NEnglish::COLLECTION_NAME_SESSION)
    )
    , CollectionBase(Master.get(), dbName, COLLECTION_NAME_BASE)
{
    INFO_LOG << "Started mongoDB" << Endl;
}

TDataSource::~TDataSource() {
    INFO_LOG << "Stopped mongoDB" << Endl;
}
