#include "user_collection.h"
#include "contrib/json/json.h"

namespace NEnglish {

    bool TCollectionUser::Register(const TRecordUser& user) {
        return Master->Insert(DbName, CollectionName, user.ToJson());
    }

    bool TCollectionUser::ExistsWithEmail(const TString& email) {
        return Master->Find(DbName, CollectionName, NJson::TJsonValue({ { "Email", email } })).size();
    }

}