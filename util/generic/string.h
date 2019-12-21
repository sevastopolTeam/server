#pragma once

#include <string>

using TString = std::string;

namespace NString {
    // int ToInt(const TString& s);

    // TString ToString(const int value);

    bool EndsWith(const TString& value, const TString& ending);

    bool Contains(const TString& value, const char searchSymbol);

    TString ToLower(TString value);

    // bool IsDigit(const char c);
}
