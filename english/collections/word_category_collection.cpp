#include "word_category_collection.h"

namespace NEnglish {
    TMaybe<TRecordWordCategory> TCollectionWordCategory::FindByName(const TString& name) {
        return FindFirst({{ RECORD_WORD_CATEGORY_FIELD_NAME, name }});
    }
}
