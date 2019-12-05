#pragma once

#include "util/generic/string.h"

namespace NEnglish {
    const TString RESPONSE_STATUS = "Status";
    const TString RESPONSE_VALIDATION_ERRORS = "ValidationErrors";
    const TString RESPONSE_ERRORS = "Errors";

    const TString RESPONSE_STATUS_OK = "Ok";
    const TString RESPONSE_STATUS_INSERT_ERROR = "InsertError";
    const TString RESPONSE_STATUS_VALIDATION_ERRROR = "ValidationError";
    const TString RESPONSE_STATUS_FATAL_ERROR = "FatalError";

    const TString RESPONSE_CONTENT_TYPE_JSON = "application/json";
}
