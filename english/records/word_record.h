#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    const TString RECORD_WORD_FIELD_ID = "Id";
    const TString RECORD_WORD_FIELD_VALUE = "Value";
    const TString RECORD_WORD_FIELD_ORIGIN_URL = "OriginUrl";  
    const TString RECORD_WORD_FIELD_LANGUAGE = "Language";


    class TRecordWord : public IRecord {
    public:
        TRecordWord() = default;
        TRecordWord(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;
        NJson::TJsonValue GetUniqSelector() const;

    private:
        // DB fields
        TString Id;
        TString Value;
        TString OriginUrl;
        TString Language
    };
}
