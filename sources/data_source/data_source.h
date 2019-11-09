#pragma once

#include "library/mongo/wrappers.h"
#include "sources/data_source/collections/base.h"
#include "util/generic/holder.h"

class TDataSource {
public:
    TDataSource(const TString& uri, const TString& db);
    ~TDataSource();

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
    TCollectionBase Base;
};
