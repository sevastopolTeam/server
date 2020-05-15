#include "translation_to_category_record.h"

#include "contrib/json/json.h"
#include "util/generic/ctype.h"

namespace NEnglish {

    TRecordTranslationToCategory::TRecordTranslationToCategory(const NJson::TJsonValue& json)
        : TranslationId(NJson::GetString(json, RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID, ""))
        , WordCategoryId(NJson::GetString(json, RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, ""))
        , IRecord(NJson::GetString(json, PATH_TO_RECORD_ID)) {}

    NJson::TJsonValue TRecordTranslationToCategory::ForDB() const {
        return {
            { RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID, TranslationId },
            { RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, WordCategoryId }
        };
    }

    NJson::TJsonValue TRecordTranslationToCategory::ToJson() const {
        NJson::TJsonValue json = ForDB();
        if (Id.has_value()) {
            json[RECORD_FIELD_ID] = *Id;
        }
        return json;
    }

}
