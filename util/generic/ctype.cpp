#include "ctype.h"
#include <cctype>

namespace NType {
    bool IsDigit(const char c) {
        return isdigit(c);
    }

    bool IsAlpha(const char c) {
        return isalpha(c);
    }

    bool IsInt(const TString& value) {
        const TString& MAX_INT = "2147483647";
        const TString& MIN_INT_PLUS = "+2147483648";
        const TString& MIN_INT = "2147483648";

        if (value.empty()) {
            return false;
        }

        if (value.front() == '-') {
            if (value.size() < 2 || value.size() > MIN_INT.size() || (value.size() == MIN_INT.size() && value > MIN_INT)) {
                return false;
            }
        } else if (value.front() == '+') {
            if (value.size() < 2 || value.size() > MAX_INT_PLUS.size() || (value.size() == MAX_INT_PLUS.size() && value > MAX_INT_PLUS)) {
                return false;
            }
        } else {
                        
        }



        if (value.empty() || (value.front() != '+' && value.front() != '-' && !IsDigit(value.front()))) {
            return false;
        }
        if ((value.front() == '+' || value.front() == '-') && value.size() < 2) {
            return false;
        }
        for (int i = 0; i < value.length(); i++) {
            if (!IsDigit(value[i])) {
                return false;
            }
        }

        return true;
    }

    bool IsUnsignedInt(const TString& value) {
        const TString& MAX_UINT = "4294967295";
        if (value.size() > MAX_UINT.size() || (value.size() == MAX_UINT.size() && value > MAX_UINT)) {
            return false;
        }
        return !value.empty() && IsDigit(value[0]) && IsInt(value);
    }

    bool IsNumber(const TString& value) {
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

    int ToInt(const TString& s) {
        return std::stoi(s);
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
