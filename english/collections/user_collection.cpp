#include "user_collection.h"
#include "contrib/json/json.h"

namespace NEnglish {

    bool TCollectionUser::Register(const TRecordUser& user) {
        return Master->Insert(DbName, CollectionName, user.ToJson());
    }

    bool TCollectionUser::ExistsWithEmail(const TString& email) {
        return Master->Find(
            DbName,
            CollectionName,
            NJson::TJsonValue({{ RECORD_USER_FIELD_EMAIL, email } })
        ).size();
    }

    TMaybe<NJson::TJsonValue> TCollectionUser::Find(const TString& user) {
        NJson::TJsonValue json;
        json["_id"]["$oid"] = user;
        TVector<NMongo::TBsonValue> results = Master->Find(
            DbName,
            CollectionName,
            json
        );
        if (results.size() == 1) {
            return results[0].ToJson();
        }
        return Nothing();
    }
}
