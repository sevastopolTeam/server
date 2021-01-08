#include "translation_to_category_collection.h"

namespace NEnglish {
    TMaybe<TRecordTranslationToCategory> TCollectionTranslationToCategory::FindByFullMatching(
        const TString& traslationId, const TString& wordCategoryId)
    {
        return FindFirst({
            { RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID, traslationId },
            { RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, wordCategoryId }
        });
    }

    TVector<TRecordTranslationToCategory> TCollectionTranslationToCategory::FindByWordCategoryId(const TString& wordCategoryId) {
        return Find({{ RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, wordCategoryId }});
    }
}
