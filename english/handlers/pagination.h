#include "contrib/httplib/httplib.h"

#include "util/generic/ctype.h"
#include "util/generic/string.h"

namespace NEnglish {
    const TString SIZE_OF_PAGE_PARAM = "PageSize";
    const TString NUMBER_OF_PAGE_PARAM = "Page";

    struct TPagination {
        int limit;
        int skip;

        TPagination(const httplib::Request& req) {
            limit = NType::ToInt(req.GetParamValue(SIZE_OF_PAGE_PARAM, "0"));
            skip = NType::ToInt(req.GetParamValue(NUMBER_OF_PAGE_PARAM, "0")) * limit;
        }
    };
}