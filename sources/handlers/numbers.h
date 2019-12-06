#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

void NumbersHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    const TString& numbers = req.matches[1];

    NJson::TJsonValue json;
    json["Hello"] = numbers;
    if (!dataSource.CollectionBase.Create(json)) {
        Cout << "error insert" << Endl;
        res.set_content("{ Error: InsertError }", "application/json");
    } else {
        res.set_content(json.dump(), "application/json");
    }
}
