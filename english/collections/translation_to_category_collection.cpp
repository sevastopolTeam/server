#include "translation_to_category_collection.h"

namespace NEnglish {
    TMaybe<TRecordTranslationToCategory> TCollectionTranslationToCategory::FindByFullMatching(
        const TString& traslationId, const TString& wordCategoryId)
    {
        return FindFirst({
            { RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRASLATION_ID, traslationId },
            { RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, wordCategoryId }
        });
    }
}
