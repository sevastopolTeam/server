#include "application.h"

#include <iostream>

#include "contrib/json/json.h"

#include "handlers/hi.h"
#include "handlers/numbers.h"

TApplication::TApplication() {
    std::cout << "Starting server..." << std::endl;
    DataSource.reset(new TDataSource("mongodb://localhost:1235", "prod", "base"));

    Server.Get("/hi",               [&](const httplib::Request& req, httplib::Response& res){ HiHandler(*DataSource, req, res);});
    Server.Get(R"(/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res){ NumbersHandler(*DataSource, req, res);});

    std::cout << "Server started" << std::endl;
    Server.listen("0.0.0.0", 1234);
}

TApplication::~TApplication() {
    std::cout << "Stopping server..." << std::endl;
    Server.stop();
    std::cout << "Server stopped" << std::endl;
}
