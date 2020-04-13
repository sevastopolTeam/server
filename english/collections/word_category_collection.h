#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/word_category_record.h"

#include "util/generic/maybe.h"

namespace NEnglish {

    class TCollectionWordCategory : public ICollection<TRecordWordCategory> {
    public:
        using ICollection::ICollection;
    };

}
