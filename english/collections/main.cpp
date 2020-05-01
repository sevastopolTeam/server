#include "main.h"

namespace NEnglish {
    const TString COLLECTION_NAME_USER = "english_user";
    const TString COLLECTION_NAME_SESSION = "english_session";
    const TString COLLECTION_NAME_TRANSLATION = "english_translation";
    const TString COLLECTION_NAME_WORD_CATEGORY = "english_word_category";
    const TString COLLECTION_NAME_TRANSLATION_TO_CATEGORY = "english_translation_to_category";

    const TString COLUMN_USER_EMAIL = "Email";
    const TString COLUMN_WORD_CATEGORY_NAME = "Name";
    const TString COLUMN_NAME_FREQUENCY = "Frequency";

    TSetOfCollections::TSetOfCollections(NMongo::THelper* master, const TString& dbName)
        : CollectionUser(master, dbName, COLLECTION_NAME_USER)
        , CollectionSession(master, dbName, COLLECTION_NAME_SESSION)
        , CollectionTranslation(master, dbName, COLLECTION_NAME_TRANSLATION)
        , CollectionWordCategory(master, dbName, COLLECTION_NAME_WORD_CATEGORY)
        , CollectionTranslationToCategory(master, dbName, COLLECTION_NAME_TRANSLATION_TO_CATEGORY)
    {
        CollectionUser.CreateIndex(NEnglish::COLUMN_USER_EMAIL, /*uniq*/ true);
        CollectionWordCategory.CreateIndex(NEnglish::COLUMN_WORD_CATEGORY_NAME, /*uniq*/ true);
        CollectionTranslation.CreateIndex(NEnglish::COLUMN_NAME_FREQUENCY, /*uniq*/ false, /*desc*/ true);
    }
}
