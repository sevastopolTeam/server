#include "user_collection.h"
#include "contrib/json/json.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    TRecordUser* TCollectionUser::FindByEmail(const TString& email) {
        TVector<NMongo::TBsonValue> result = Master->Find(
            DbName,
            CollectionName,
            NJson::TJsonValue({{ RECORD_USER_FIELD_EMAIL, email }})
        );

        if (!result.size()) {
            return nullptr;
        }
        // get json
        NJson::TJsonValue json = result[0].ToJson();
        json[RECORD_USER_FIELD_ID] = json["_id"].value("$oid", "");
        return new TRecordUser(json);
    }

    bool TCollectionUser::ExistsWithEmail(const TString& email) {
        return Exists({{ RECORD_USER_FIELD_EMAIL, email }});
    }

}
