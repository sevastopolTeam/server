#include "user_collection.h"
#include "contrib/json/json.h"

namespace NEnglish {

    bool TCollectionUser::ExistsWithEmail(const TString& email) {
        return Master->Find(
            DbName,
            CollectionName,
            NJson::TJsonValue({{ RECORD_USER_FIELD_EMAIL, email } })
        ).size();
    }

}
