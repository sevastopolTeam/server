#pragma once

#include <cctype>

#include "string.h"
#include "vector.h"
#include "maybe.h"
#include "iostream.h"
#include "vector.h"

#include "contrib/json/json.h"


struct NType {
    static bool IsDigit(const char c) {
        return isdigit(c);
    }

    static bool IsAlpha(const char c) {
        return isalpha(c);
    }

    static bool IsInteger(const TString& value) {
        if (value.empty() || (value[0] != '+' && value[0] != '-' && !IsDigit(value[0]))) {
            return false;
        }
        for (int i = 0; i < value.length(); i++) {
            if (!IsDigit(value[i])) {
                return false;
            }
        }

        return true;
    }

    static bool IsNumber(const TString& value) {
        if (value.empty() || (value[0] != '+' && value[0] != '-' && !IsDigit(value[0]))) {
            return false;
        }
        bool wasPoint = false;
        for (int i = 0; i < value.length(); i++) {
            if (value[i] == '.') {
                if (wasPoint) {
                    return false;
                }
                wasPoint = true;
                continue;
            }
            if (!IsDigit(value[i])) {
                return false;
            }
        }

        return true;
    }

    static int ToInt(const TString& s) {
        return std::stoi(s);
    }

    static TString ToString(const int value) {
        return std::to_string(value);
    }

    static TString ToString(const float value) {
        return std::to_string(value);
    }

    static TString ToString(const double value) {
        return std::to_string(value);
    }

};

namespace NJson {
    TJsonValue GetJson(const TJsonValue& value, const TString& path) {
        TJsonValue result = value;
        TString key;
        for (int i = 0; i <= path.length(); i++) {
            if (i != path.length() && path[i] != '.') {
                key.push_back(path[i]);
            }
         else {
                if (result.find(key) == result.end()) {
                    return nullptr;
                }
                result = result[key];
                key.clear();
            }
        }

        return result;
    }

    bool GetBool(const TJsonValue& value, const TString& path, const bool defaultValue) {
        const TJsonValue& result = GetJson(value, path);
        if (result.is_null()) {
            return defaultValue;
        }
        if (result.is_string()) {
            return result.get<TString>() != "";
        }
        if (result.is_number()) {
            return result.get<int>() != 0;
        }
        return result.get<bool>();
    }

    TMaybe<int> GetInt(const TJsonValue& value, const TString& path) {
        const TJsonValue& result = GetJson(value, path);
        if (result.is_null()) {
            return Nothing();
        }
        if (result.is_string()) {
            return NType::ToInt(result.get<TString>());
        }
        return result.get<int>();
    }

    int GetInt(const TJsonValue& value, const TString& path, const int defaultValue) {
        const auto& mayResult = GetInt(value, path);
        if (!mayResult.has_value()) {
            return defaultValue;
        }

        return *mayResult;
    }

    TMaybe<TString> GetString(const TJsonValue& value, const TString& path) {
        const TJsonValue& result = GetJson(value, path);
        if (result.is_null()) {
            return Nothing();
        }
        if (result.is_number()) {
            return NType::ToString(result.get<int>());
        }
        return result.get<TString>();
    }

    TString GetString(const TJsonValue& value, const TString& path, const TString& defaultValue) {
        const auto& mayResult = GetString(value, path);
        if (!mayResult.has_value()) {
            return defaultValue;
        }

        return *mayResult;
    }

    template <class T>
    TJsonValue GetVectorJson(const TVector<T>& v) {
        TJsonValue result;
        for (const auto& item: v) {
            result.push_back(item.ToJson());
        }

        return result;
    }
}