#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

void NumbersHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");

    NJson::TJsonValue json;
    json["Hello"] = TString(numbers);
    if (!dataSource.CollectionBase.Insert(json)) {
        Cout << "error insert" << Endl;
    }
}
