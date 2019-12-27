#pragma once

#include <string>

using TString = std::string;

namespace NString {
    bool EndsWith(const TString& value, const TString& ending);
    bool Contains(const TString& value, const char searchSymbol);
    TString ToLower(TString value);
}
