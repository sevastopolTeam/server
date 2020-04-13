#pragma once

#include "contrib/json/json.h"
#include "sources/records/record.h"
#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {

    const TString RECORD_WORD_CATEGORY_FIELD_NAME = "Name";

    class TRecordWordCategory : public IRecord {
    public:
        TRecordWordCategory() = default;
        TRecordWordCategory(const NJson::TJsonValue& json);

        NJson::TJsonValue ToJson() const override;
        NJson::TJsonValue ForDB() const override;

    private:
        TString Name;
    };
}
