#include "translation_record.h"

#include <ctime>

#include "contrib/json/json.h"

#include "util/generic/iostream.h"
#include "util/generic/hash_functions.h"
#include "util/generic/ctype.h"

namespace {
    TString Normalize(const TString& str) {
        return NString::ToLower(str);
    }
}

namespace NEnglish {

    TRecordTranslation::TRecordTranslation(const NJson::TJsonValue& json)
        : ValueFrom(Normalize(NJson::GetString(json, RECORD_TRANSLATION_FIELD_VALUE_FROM, "")))
        , ValueTo(Normalize(NJson::GetString(json, RECORD_TRANSLATION_FIELD_VALUE_TO, "")))
        , LanguageFrom(NJson::GetString(json, RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, ""))
        , LanguageTo(NJson::GetString(json, RECORD_TRANSLATION_FIELD_LANGUAGE_TO, ""))
        , OriginUrl(NJson::GetString(json, RECORD_TRANSLATION_FIELD_ORIGIN_URL, ""))
        , IRecord(NJson::GetString(json, "_id.$oid"))
    {}

    NJson::TJsonValue TRecordTranslation::ToJson() const {
        return {
            {RECORD_TRANSLATION_FIELD_VALUE_FROM, ValueFrom},
            {RECORD_TRANSLATION_FIELD_VALUE_TO, ValueTo},
            {RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, LanguageFrom},
            {RECORD_TRANSLATION_FIELD_LANGUAGE_TO, LanguageTo},
            {RECORD_TRANSLATION_FIELD_ORIGIN_URL, OriginUrl}
        };
    }

}
