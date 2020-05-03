#pragma once

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "sources/data_source/data_source.h"

namespace NEnglish {
    void GetAdminSessionsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
}
