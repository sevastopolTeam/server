#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/translation_to_category_record.h"

#include "util/generic/maybe.h"

namespace NEnglish {

    class TCollectionTranslationToCategory : public ICollection<TRecordTranslationToCategory> {
    public:
        using ICollection::ICollection;

        // TMaybe<TRecordTranslationToCategory> FindByName(const TString& name);
    };

}
