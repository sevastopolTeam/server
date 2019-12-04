#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/user_record.h"

namespace NEnglish {

    class TCollectionUser : public ICollection {
    public:
        using ICollection::ICollection;

        bool Register(const TRecordUser& user);
        bool ExistsWithEmail(const TString& email);
        // TMaybe<NJson::TJsonValue> Find(const TString& user);
        NJson::TJsonValue Find(const TString& user);
    };

}