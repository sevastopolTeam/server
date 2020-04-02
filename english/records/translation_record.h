#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    const TString RECORD_TRANSLATION_FIELD_ID = "Id";
    const TString RECORD_TRANSLATION_FIELD_VALUE_FROM = "ValueFrom";
    const TString RECORD_TRANSLATION_FIELD_VALUE_TO = "ValueTo";
    const TString RECORD_TRANSLATION_FIELD_LANGUAGE_FROM = "LanguageFrom";
    const TString RECORD_TRANSLATION_FIELD_LANGUAGE_TO = "LanguageTo";
    const TString RECORD_TRANSLATION_FIELD_ORIGIN_URL = "OriginUrl";

    class TRecordTranslation : public IRecord {
    public:
        TRecordTranslation() = default;
        TRecordTranslation(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;
        // NJson::TJsonValue GetUniqSelector() const;

    private:
        // DB fields
        TString ValueFrom;
        TString ValueTo;
        TString LanguageFrom;
        TString LanguageTo;
        TString OriginUrl;
    };
}