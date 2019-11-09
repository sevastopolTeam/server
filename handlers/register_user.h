#pragma once

#include <iostream>

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

void RegisterUserHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    auto user = NJson::TJsonValue::parse(req.body);
    std::cout << user.dump(4) << std::endl;
    if (dataSource.User.Register(user)) {
        res.set_content("user registered", "text/plain");
    } else {
        res.set_content("user already register", "text/plain");
    }
}
