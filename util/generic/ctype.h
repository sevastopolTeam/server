#pragma once

#include "string.h"
#include "vector.h"
#include "maybe.h"

#include "contrib/json/json.h"

namespace NType {
    bool IsDigit(const char c);
    bool IsAlpha(const char c);
    bool IsInt(const TString& value);
    bool IsUnsignedInt(const TString& value);
    bool IsInt32(const TString& value);
    bool IsUnsignedInt32(const TString& value);
    bool IsNumber(const TString& value);
    bool LessThan(const TString& value, const int compareValue);

    int ToInt(const TString& s);

    template <class T>
    TString ToString(const T& value);
}

namespace NJson {
    TJsonValue GetJson(const TJsonValue& value, const TString& path);
    bool GetBool(const TJsonValue& value, const TString& path, const bool defaultValue);

    TMaybe<int> GetInt(const TJsonValue& value, const TString& path);

    int GetInt(const TJsonValue& value, const TString& path, const int defaultValue);

    TMaybe<TString> GetString(const TJsonValue& value, const TString& path);

    TString GetString(const TJsonValue& value, const TString& path, const TString& defaultValue);

    template <class T>
    TJsonValue ToVectorJson(const TVector<T>& v);
}


template <class T>
TString NType::ToString(const T& value) {
    return std::to_string(value);
}

template <class T>
NJson::TJsonValue NJson::ToVectorJson(const TVector<T>& v) {
    TJsonValue result;
    for (const auto& item: v) {
        result.push_back(item.ToJson());
    }

    return result;
}
