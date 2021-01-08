#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    const TString RECORD_TRANSLATION_FIELD_RUSSIAN = "Russian";
    const TString RECORD_TRANSLATION_FIELD_ENGLISH = "English";
    const TString RECORD_TRANSLATION_FIELD_ORIGIN_URL = "OriginUrl";
    const TString RECORD_TRANSLATION_FIELD_DOWNLOAD_URL = "DownloadUrl";
    const TString RECORD_TRANSLATION_FIELD_PART_OF_SPEECH = "PartOfSpeech";
    const TString RECORD_TRANSLATION_FIELD_IS_CHECKED = "IsChecked";
    const TString RECORD_TRANSLATION_FIELD_FREQUENCY = "Frequency";

    class TRecordTranslation : public IRecord {
    public:
        TRecordTranslation() = default;
        TRecordTranslation(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;
        NJson::TJsonValue ForDB() const override;

        TString GetRussian() const;

    private:
        // DB fields
        TString Russian;
        TString English;
        TString OriginUrl;
        TString DownloadUrl;
        TString PartOfSpeech;
        unsigned int Frequency;
        bool IsChecked;
    };
}
