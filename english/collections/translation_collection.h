#pragma once

#include "sources/collections/collection.h"
#include "english/records/translation_record.h"
#include "util/generic/maybe.h"
#include "util/generic/vector.h"

namespace NEnglish {

    class TCollectionTranslation : public ICollection<TRecordTranslation> {
    public:
        using ICollection::ICollection;

        TMaybe<TRecordTranslation> FindByFullMatching(
            const TString& russian,
            const TString& english
        );

        TVector<TRecordTranslation> FindByWord(const TString& word, const size_t limit = 0);

        NJson::TJsonValue JsonForSortingDefault() const;

    };

}
