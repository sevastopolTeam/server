#include "application.h"

#include <iostream>

#include "contrib/json/json.h"

#include "sources/handlers/hi.h"
#include "sources/handlers/numbers.h"

#include "english/handlers/register_user.h"

TApplication::TApplication() {
    std::cout << "Starting server..." << std::endl;
    DataSource.reset(new TDataSource("mongodb://localhost:1235", "prod"));
    Server.reset(new httplib::Server());

    Server->Get("/api/admin/hi", [&](const httplib::Request& req, httplib::Response& res) {
        HiHandler(*DataSource, req, res);
    });
    Server->Get(R"(/api/admin/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        NumbersHandler(*DataSource, req, res);
    });

    Server->Post("/api/english/register_user", [&](const httplib::Request& req, httplib::Response& res) {
        RegisterUserHandler(*DataSource, req, res);
    });
}

void TApplication::Start() {
    std::cout << "Started HTTP-server" << std::endl;
    Server->listen("0.0.0.0", 1234);
}

TApplication::~TApplication() {
    Server->stop();
    std::cout << "Stopped HTTP-server" << std::endl;
}
