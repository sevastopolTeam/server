#include "main.h"

namespace NEnglish {
    const TString COLLECTION_NAME_USER = "english_user";
    const TString COLLECTION_NAME_SESSION = "english_session";
    const TString COLLECTION_NAME_TRANSLATION = "english_translation";
    const TString COLLECTION_NAME_WORD_CATEGORY = "english_word_category";

    const TString COLUMN_NAME_EMAIL = "Email";

    TSetOfCollections::TSetOfCollections(NMongo::THelper* master, const TString& dbName)
        : CollectionUser(master, dbName, COLLECTION_NAME_USER)
        , CollectionSession(master, dbName, COLLECTION_NAME_SESSION)
        , CollectionTranslation(master, dbName, COLLECTION_NAME_TRANSLATION)
        , CollectionWordCategory(master, dbName, COLLECTION_NAME_WORD_CATEGORY)
    {
        CollectionUser.CreateIndex(NEnglish::COLUMN_NAME_EMAIL, /*uniq*/ true);
    }
}
