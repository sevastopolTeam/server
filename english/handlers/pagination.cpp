#include "pagination.h"

#include "util/generic/ctype.h"

namespace NEnglish {        
    TPagination::TPagination(const httplib::Request& req) {
        limit = NType::ToInt(req.GetParamValue(SIZE_OF_PAGE_PARAM, "0"));
        skip = NType::ToInt(req.GetParamValue(NUMBER_OF_PAGE_PARAM, "0")) * limit;
    }
}
