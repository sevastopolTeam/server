#pragma once

#include <cctype>

#include "string.h"
#include "vector.h"

#include "contrib/json/json.h"

#include "util/generic/maybe.h"
#include "util/generic/iostream.h"

struct NType {
    static bool IsDigit(const char c) {
        return isdigit(c);
    }

    static bool IsAlpha(const char c) {
        return isalpha(c);
    }

    static bool IsNumber(const TString& value) {
        if (value.empty() || (value[0] != '+' && value[0] != '-' && !IsDigit(value[0]))) {
            return false;
        }
        for (int i = 0; i < value.length(); i++) {
            if (!IsDigit(s[i])) {
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
        if (value.find(path) == value.end()) {
            return nullptr;
        }

        return value[path];
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
        if (!mayResult.Empty()) {
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
        return res.get<TString>();
    }

    TString GetString(const TJsonValue& value, const TString& path, const TString& defaultValue) {
        const auto& mayResult = GetString(value, path);
        if (!mayResult.Empty()) {
            return defaultValue;
        }

        return *mayResult;
    }
};