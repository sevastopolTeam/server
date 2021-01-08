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
        : Russian(Normalize(NJson::GetString(json, RECORD_TRANSLATION_FIELD_RUSSIAN, "")))
        , English(Normalize(NJson::GetString(json, RECORD_TRANSLATION_FIELD_ENGLISH, "")))
        , OriginUrl(NJson::GetString(json, RECORD_TRANSLATION_FIELD_ORIGIN_URL, ""))
        , DownloadUrl(NJson::GetString(json, RECORD_TRANSLATION_FIELD_DOWNLOAD_URL, ""))
        , PartOfSpeech(NJson::GetString(json, RECORD_TRANSLATION_FIELD_PART_OF_SPEECH, ""))
        , Frequency(NJson::GetInt(json, RECORD_TRANSLATION_FIELD_FREQUENCY, 0))
        , IsChecked(NJson::GetBool(json, RECORD_TRANSLATION_FIELD_IS_CHECKED, false))
        , IRecord(NJson::GetString(json, PATH_TO_RECORD_ID))
    {}

    TString TRecordTranslation::GetRussian() const {
        return Russian;
    }

    NJson::TJsonValue TRecordTranslation::ForDB() const {
        return {
            {RECORD_TRANSLATION_FIELD_RUSSIAN, Russian},
            {RECORD_TRANSLATION_FIELD_ENGLISH, English},
            {RECORD_TRANSLATION_FIELD_ORIGIN_URL, OriginUrl},
            {RECORD_TRANSLATION_FIELD_DOWNLOAD_URL, DownloadUrl},
            {RECORD_TRANSLATION_FIELD_PART_OF_SPEECH, PartOfSpeech},
            {RECORD_TRANSLATION_FIELD_FREQUENCY, Frequency},
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
