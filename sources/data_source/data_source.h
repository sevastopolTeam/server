#pragma once

#include "library/mongo/wrappers.h"
#include "util/generic/holder.h"

#include "sources/collections/base.h"
#include "english/collections/main.h"

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
    NEnglish::TSetOfCollections English;
};
