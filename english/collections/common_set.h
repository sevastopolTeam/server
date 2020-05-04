#pragma once

#include "english/collections/user_collection.h"
#include "english/collections/session_collection.h"
#include "english/collections/translation_collection.h"
#include "english/collections/word_category_collection.h"
#include "english/collections/translation_to_category_collection.h"

class TDataSource;

namespace NEnglish {

    struct TSetOfCollections {
        NEnglish::TCollectionUser CollectionUser;
        NEnglish::TCollectionSession CollectionSession;
        NEnglish::TCollectionTranslation CollectionTranslation;
        NEnglish::TCollectionWordCategory CollectionWordCategory;
        NEnglish::TCollectionWordCategory CollectionTranslationToCategory;

        TSetOfCollections(NMongo::THelper* master, const TString& dbName, TDataSource* dataSource);
    };

}
