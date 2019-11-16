#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/user_record.h"

class TCollectionEnglishUser : public ICollection {
public:
    using ICollection::ICollection;

    bool Register(const TRecordEnglishUser& user);
    bool IsAlreadyRegistred(const TRecordEnglishUser& user);
};
