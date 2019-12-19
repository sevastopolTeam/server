#include "hash_functions.h"
#include "ctype.h"

#include "contrib/md5/md5.h"
#include <ctime>

namespace NHashFunctions {

    TString GenerateRandomToken() {
        return md5(NType::ToString(rand())) + NType::ToString(time(NULL));
    }

    TString GeneratePasswordHash(const TString& password) {
        return md5(password);
    }
}
