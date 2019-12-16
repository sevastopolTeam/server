#pragma once

#include <cctype>

struct NType {
    static int ToInt(const TString& s) {
        return std::stoi(s);
    }

    static TString ToString(const int value) {
        return std::to_string(value);
    }

    static bool IsDigit(const char c) {
        return isdigit(c);
    }

    static bool IsAlpha(const char c) {
        return isdigit(c);
    }
};