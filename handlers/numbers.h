#pragma once

#include "data_source.h"
#include "contrib/httplib/httplib.h"
#include "library/mongo/wrappers.h"

void NumbersHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
	auto numbers = req.matches[1];
	res.set_content(numbers, "text/plain");

    NJson::TJsonValue json;
    json["hello"] = TString(numbers);
    if (!dataSource.Insert(json)) {
        std::cout << "error insert" << std::endl;
    }
}
