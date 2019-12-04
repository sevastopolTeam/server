#include "user_collection.h"
#include "contrib/json/json.h"

#include "util/generic/iostream.h"

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

    // TMaybe<NJson::TJsonValue> TCollectionUser::Find(const TString& user) {
    NJson::TJsonValue TCollectionUser::Find(const TString& user) {
        Cout << "aaaa" << Endl;
        NJson::TJsonValue json;
        json["query"]["_id"]["$oid"] = user;
        Cout << "bbbb" << Endl;
        Cout << json.dump() << Endl;
        TVector<NMongo::TBsonValue> results = Master->Find(
            DbName,
            CollectionName,
            json
        );
        Cout << "cccc" << Endl;
        if (results.size() == 1) {
            return results[0].ToJson();
        }
        Cout << "dddd" << Endl;
        return {};//Nothing();
    }
}
