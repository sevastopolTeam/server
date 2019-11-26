#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/base.h"
#include "util/generic/holder.h"

#include "english/collections/user_collection.h"
#include "english/collections/session_collection.h"

struct TEnglishCollections {
    NEnglish::TCollectionUser CollectionUser;
    NEnglish::TCollectionSession CollectionSession;

    TEnglishCollections(
        const NEnglish::TCollectionUser& collectionUser,
        const NEnglish::TCollectionSession& collectionSession
    );
};

class TDataSource {
public:
    TDataSource(const TString& uri, const TString& db);
    ~TDataSource();

private:
    struct TMongoDriver {
        TMongoDriver() {
            NMongo::Init();
        }
        ~TMongoDriver() {
            NMongo::Cleanup();
        }
    };

    TMongoDriver MongoDriver;
    THolder<NMongo::THelper> Master;

public:
    TCollectionBase CollectionBase;
    TEnglishCollections English;
};
