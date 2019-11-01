#pragma once

#include <string>

using TString = std::string;

namespace NString {
    int ToInt(const TString& s) {
        return std::stoi(s);
    }

    TString ToString(const int value) {
        return std::to_string(value);
    }

    bool EndsWith(const TString& value, const TString& ending) {
        if (ending.size() > value.size()) {
            return false;
        }
        return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
    }
}
