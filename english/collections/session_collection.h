#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/session_record.h"

namespace NEnglish {

    class TCollectionSession : public ICollection<TRecordSession> {
    public:

        static TString COLLECTION_NAME = "Translations";

        using ICollection::ICollection;
        TMaybe<TRecordSession> FindByToken(const TString& token);
        bool RemoveByToken(const TString& token);
    };

}
