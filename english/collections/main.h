#include "english/collections/user_collection.h"
#include "english/collections/session_collection.h"

namespace NEnglish {

    struct TSetOfCollections {
        NEnglish::TCollectionUser CollectionUser;
        NEnglish::TCollectionSession CollectionSession;

        TSetOfCollections(NMongo::THelper* master, const TString& dbName);
    };

}