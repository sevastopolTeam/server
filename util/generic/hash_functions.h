#pragma once

#include <ctime>

#include "string.h"
#include "contrib/md5/md5.h"

struct NHashFunctions {

    static TString GenerateRandomToken() {
        return md5(NString::ToString(rand())) + NString::ToString(time(NULL));
    }

    static TString GeneratePasswordHash(const TString& password) {
        return md5(password);
    }
};
