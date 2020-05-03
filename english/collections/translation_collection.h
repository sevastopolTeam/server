#pragma once

#include "library/mongo/wrappers.h"
#include "sources/collections/collection.h"

#include "english/records/translation_record.h"

#include "util/generic/maybe.h"

namespace NEnglish {
    
    class TCollectionTranslation : public ICollection<TRecordTranslation> {
    public:
        using ICollection::ICollection;

        TMaybe<TRecordTranslation> FindByFullMatching(
            const TString& valueFrom,
            const TString& valueTo,
            const TString& languageFrom,
            const TString& languageTo
        );

    };

}
