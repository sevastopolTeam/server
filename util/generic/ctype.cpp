#include "ctype.h"
#include <cctype>

#include "string.h"

#include "iostream.h"

namespace NType {

    const TString& MAX_INT_32 = "2147483647";
    const TString& MAX_INT_32_PLUS = "+2147483648";
    const TString& MIN_INT_32 = "2147483648";
    const TString& MAX_UINT_32 = "4294967295";

    bool IsDigit(const char c) {
        return isdigit(c);
    }

    bool IsAlpha(const char c) {
        return isalpha(c);
    }

    bool IsInt(const TString& value) {
        if (value.empty()) {
            return false;
        }
        size_t startDigit = 0;
        if (value.front() == '+' || value.front() == '-') {
            if (value.size() < 2) {
                return false;
            }
            startDigit = 1;
        }
        for (int i = startDigit; i < value.length(); i++) {
            if (!IsDigit(value[i])) {
                return false;
            }
        }

        return true;
    }

    bool IsInt32(const TString& value) {
        if (!IsInt(value)) {
            return false;
        }

        if (value.front() == '-') {
            if (value.size() > MIN_INT_32.size() || (value.size() == MIN_INT_32.size() && value > MIN_INT_32)) {
                return false;
            }
        } else if (value.front() == '+') {
            if (value.size() > MAX_INT_32_PLUS.size() || (value.size() == MAX_INT_32_PLUS.size() && value > MAX_INT_32_PLUS)) {
                return false;
            }
        } else {
            if (value.size() > MAX_INT_32.size() || (value.size() == MAX_INT_32.size() && value > MAX_INT_32)) {
                return false;
            }
        }

        return true;
    }

    bool IsUnsignedInt(const TString& value) {
        return IsInt(value) && IsDigit(value.front());
    }

    bool IsUnsignedInt32(const TString& value) {
        if (!IsUnsignedInt(value)) {
            return false;
        }
        return value.size() < MAX_UINT_32.size() || (value.size() == MAX_UINT_32.size() && value < MAX_UINT_32);
    }

    bool IsNumber(const TString& value) {
        if (value.empty()) {
            return false;
        }
        size_t startDigit = 0;
        if (value.front() == '+' || value.front() == '-') {
            if (value.size() < 2 || !IsDigit(value[1])) {
                return false;
            }
            startDigit = 1;
        }
        bool wasPoint = false;
        for (int i = startDigit; i < value.length(); i++) {
            if (value[i] == '.') {
                if (wasPoint) {
                    return false;
                }
                wasPoint = true;
            } else if (!IsDigit(value[i])) {
                return false;
            }
        }

        return true;
    }

    int ToInt(const TString& s) {
        return std::stoi(s);
    }

    bool LessThan(const TString& value, const int compareValue) {
        if (!IsInt(value)) {
            throw("Value bust be int");
        }
        return IsInt32(value) && ToInt(value) < compareValue;
    }

}

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
}
