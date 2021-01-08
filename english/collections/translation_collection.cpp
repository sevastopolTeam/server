#include "translation_collection.h"

#include "contrib/json/json.h"

#include "util/generic/iostream.h"

namespace NEnglish {
    TMaybe<TRecordTranslation> TCollectionTranslation::FindByFullMatching(
            const TString& russian,
            const TString& english
    ) {
        return FindFirst({
            { RECORD_TRANSLATION_FIELD_RUSSIAN, russian },
            { RECORD_TRANSLATION_FIELD_ENGLISH, english }
        });
    }

    TVector<TRecordTranslation> TCollectionTranslation::FindByWord(const TString& word, const size_t limit) {
        NJson::TJsonValue selection;
        selection[RECORD_TRANSLATION_FIELD_RUSSIAN] = {
            { "$regex", "^" + word },
            { "$options", ""}
        };
        return Find(selection, 0, limit, JsonForSortingDefault());
    }

    NJson::TJsonValue TCollectionTranslation::JsonForSortingDefault() const {
        return {{ RECORD_TRANSLATION_FIELD_FREQUENCY, -1 }};
    }

}
