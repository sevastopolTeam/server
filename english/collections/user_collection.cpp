#include "user_collection.h"
#include "contrib/json/json.h"

#include "util/generic/iostream.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    TMaybe<TRecordUser> TCollectionUser::FindByEmail(const TString& email) {
        TVector<TRecordUser> records = FindBy({{ "Email", email }});
        if (records.empty()) {
            return Nothing();
        }
        return records[0];
    }

    bool TCollectionUser::ExistsWithEmail(const TString& email) {
        return Exists({{ RECORD_USER_FIELD_EMAIL, email }});
    }

}
