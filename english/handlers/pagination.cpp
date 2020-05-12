#include "pagination.h"

#include "util/generic/ctype.h"
#include "util/generic/string.h"

namespace NEnglish {        
    TPagination::TPagination(const httplib::Request& req) {
        const TString& sizeOfPage = req.GetParamValue(SIZE_OF_PAGE_PARAM, "0");
        const TString& numberOfPage = req.GetParamValue(NUMBER_OF_PAGE_PARAM, "0");
        limit = NType::IsInt32(sizeOfPage) ? NType::ToInt(sizeOfPage) : 0;
        skip = NType::IsInt32(numberOfPage) ? NType::ToInt(numberOfPage) * limit : 0;
    }
}
