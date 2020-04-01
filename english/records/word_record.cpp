#include "word_record.h"

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

    TRecordWord::TRecordWord(const NJson::TJsonValue& json)
        : Value(Normalize(NJson::GetString(json, RECORD_WORD_FIELD_VALUE, "")))
        , OriginUrl(NJson::GetString(json, RECORD_WORD_FIELD_ORIGIN_URL, ""))
        , Language(NJson::GetString(json, RECORD_WORD_FIELD_LANGUAGE, ""))
    {
        Id = NJson::GetString(json, "_id.$oid");
    }

    NJson::TJsonValue TRecordWord::ToJson() const {
        return {
            {RECORD_WORD_FIELD_VALUE, Value},
            {RECORD_WORD_FIELD_ORIGIN_URL, OriginUrl},
            {RECORD_WORD_FIELD_LANGUAGE, Language}
        };
    }

}
