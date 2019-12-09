#include "user_collection.h"
#include "contrib/json/json.h"

#include "util/generic/iostream.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    TMaybe<TRecordUser> TCollectionUser::FindByEmail(const TString& email) {
        return FindBy({{ "Email", email }});
    }

    bool TCollectionUser::ExistsWithEmail(const TString& email) {
        return Exists({{ RECORD_USER_FIELD_EMAIL, email }});
    }

}
