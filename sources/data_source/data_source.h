#pragma once

#include "collections/base.h"
#include "collections/user.h"
#include "library/mongo/wrappers.h"
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
    TCollectionUser User;
};
