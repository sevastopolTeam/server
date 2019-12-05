#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

void HiHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    TVector<TRecordBase> records = dataSource.CollectionBase.Find();
    NJson::TJsonValue response;
    for (const auto& record: records) {
        response.push_back(record.ToJson());
    }

    INFO_LOG << response.dump() << Endl;
    res.set_content(response.dump(), "text/plain");
}

