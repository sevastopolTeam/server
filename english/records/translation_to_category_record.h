#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    const TString RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID = "TranslationId";
    const TString RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID = "WordCategoryId";

    class TRecordTranslationToCategory : public IRecord {
    public:
        TRecordTranslationToCategory() = default;
        TRecordTranslationToCategory(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;
        NJson::TJsonValue ForDB() const override;

        TString GetTranslationId() const;

    private:
        TString TranslationId;
        TString WordCategoryId;
    };
}
