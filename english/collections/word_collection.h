#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/word_record.h"

namespace NEnglish {

    class TCollectionWord : public ICollection<TRecordWord> {
    public:
        using ICollection::ICollection;
    };

}