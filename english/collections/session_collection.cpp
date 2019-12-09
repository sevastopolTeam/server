#include "session_collection.h"
#include "contrib/json/json.h"

namespace NEnglish {
    TMaybe<TRecordSession> TCollectionSession::FindByToken(const TString& token) {
        return FindBy({{ RECORD_SESSION_FIELD_TOKEN, token }});
    }
}
