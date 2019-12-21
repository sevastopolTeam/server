#include "string.h"

#include <cctype>

using TString = std::string;

namespace NString {
    // int ToInt(const TString& s) {
    //     return std::stoi(s);
    // }

    // TString ToString(const int value) {
    //     return std::to_string(value);
    // }

    bool EndsWith(const TString& value, const TString& ending) {
        if (ending.size() > value.size()) {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }

    bool Contains(const TString& value, const char searchSymbol) {
        return value.find(searchSymbol) != TString::npos;
    }

    TString ToLower(TString value) {
        for (auto c: value) {
            if (isalpha(c)) {
                c = tolower(c);
            }
        }

        return value;
    }

    // bool IsDigit(const char c) {
    //     return isdigit(c);
    // }
}
