#pragma once

#include "string.h"

namespace NHashFunctions {
    TString GenerateRandomToken();
    TString GeneratePasswordHash(const TString& password);
}
