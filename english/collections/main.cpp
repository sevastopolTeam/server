#include "main.h"

namespace NEnglish {
    const TString COLLECTION_NAME_USER = "english_user";
    const TString COLLECTION_NAME_SESSION = "english_session";
    const TString COLLECTION_NAME_TRANSLATION = "english_translation";

    const TString COLUMN_NAME_EMAIL = "Email";
    const TString COLUMN_NAME_FREQUENCY = "Frequency";

    TSetOfCollections::TSetOfCollections(NMongo::THelper* master, const TString& dbName, TDataSource* dataSource)
        : CollectionUser(master, dbName, COLLECTION_NAME_USER, dataSource)
        , CollectionSession(master, dbName, COLLECTION_NAME_SESSION, dataSource)
        , CollectionTranslation(master, dbName, COLLECTION_NAME_TRANSLATION, dataSource)
    {
        CollectionUser.CreateIndex(NEnglish::COLUMN_NAME_EMAIL, /*uniq*/ true);
        CollectionTranslation.CreateIndex(NEnglish::COLUMN_NAME_FREQUENCY, /*uniq*/ false, /*desc*/ true);
    }
}
