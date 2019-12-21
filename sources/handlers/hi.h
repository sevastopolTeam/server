#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

void HiHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    NJson::TJsonValue response = NJson::ToVectorJson(dataSource.CollectionBase.Find());
    INFO_LOG << response.dump() << Endl;
    res.set_content(response.dump(), "text/plain");
}

