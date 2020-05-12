#pragma once

#include "sources/collections/collection.h"
#include "english/records/user_record.h"

namespace NEnglish {

    class TCollectionUser : public ICollection<TRecordUser> {
    public:
        using ICollection::ICollection;

        TMaybe<TRecordUser> FindByEmail(const TString& email);
        bool ExistsWithEmail(const TString& email);
    };

}