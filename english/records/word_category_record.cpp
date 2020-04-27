#include "word_category_record.h"

#include "contrib/json/json.h"
#include "util/generic/ctype.h"

namespace NEnglish {

    TRecordWordCategory::TRecordWordCategory(const NJson::TJsonValue& json)
        : Name(NJson::GetString(json, RECORD_WORD_CATEGORY_FIELD_NAME, ""))
        , IRecord(NJson::GetString(json, PATH_TO_RECORD_ID)) {}

    NJson::TJsonValue TRecordWordCategory::ForDB() const {
        return {
            {RECORD_WORD_CATEGORY_FIELD_NAME, Name}
        };
    }

    NJson::TJsonValue TRecordWordCategory::ToJson() const {
        NJson::TJsonValue json = ForDB();
        if (Id.has_value()) {
            json[RECORD_FIELD_ID] = *Id;
        }
        return json;
    }

}
