#include "translation_record.h"

#include "contrib/json/json.h"
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
        , DownloadUrl(NJson::GetString(json, RECORD_TRANSLATION_FIELD_DOWNLOAD_URL, ""))
        , IsChecked(NJson::GetBool(json, RECORD_TRANSLATION_FIELD_IS_CHECKED, false))
        , IRecord(NJson::GetString(json, PATH_TO_RECORD_ID))
    {}

    NJson::TJsonValue TRecordTranslation::ForDB() const {
        return {
            {RECORD_TRANSLATION_FIELD_VALUE_FROM, ValueFrom},
            {RECORD_TRANSLATION_FIELD_VALUE_TO, ValueTo},
            {RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, LanguageFrom},
            {RECORD_TRANSLATION_FIELD_LANGUAGE_TO, LanguageTo},
            {RECORD_TRANSLATION_FIELD_ORIGIN_URL, OriginUrl},
            {RECORD_TRANSLATION_FIELD_DOWNLOAD_URL, DownloadUrl},
            {RECORD_TRANSLATION_FIELD_IS_CHECKED, IsChecked}
        };
    }

    NJson::TJsonValue TRecordTranslation::ToJson() const {
        NJson::TJsonValue json = ForDB();
        if (Id.has_value()) {
            json[RECORD_FIELD_ID] = *Id;
        }
        return json;
    }

}
