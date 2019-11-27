#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/session_record.h"

namespace NEnglish {

    class TCollectionSession : public ICollection {
    public:
        using ICollection::ICollection;

        bool Create(const TRecordSession& session);
        TVector<TRecordSession> Find();
    };

}
