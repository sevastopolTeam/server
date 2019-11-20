#pragma once

#include <string>
#include <cctype>

using TString = std::string;

struct NString {
    static int ToInt(const TString& s) {
        return std::stoi(s);
    }

    static TString ToString(const int value) {
        return std::to_string(value);
    }

    static bool EndsWith(const TString& value, const TString& ending) {
        if (ending.size() > value.size()) {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    static bool Contains(const TString& value, const char searchSymbol) {
        return value.find(searchSymbol) != TString::npos;
    }

    static TString ToLower(TString value) {
        for (auto c: value) {
            if (isalpha(c)) {
                c = tolower(c);
            }
        }

        return value;
    }
};
