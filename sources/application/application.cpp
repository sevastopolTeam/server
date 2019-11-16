#include "application.h"

#include <iostream>

#include "contrib/json/json.h"

#include "sources/handlers/hi.h"
#include "sources/handlers/numbers.h"

#include "english/handlers/registration.h"

TApplication::TApplication() {
    Cout << "Starting server..." << Endl;
    DataSource.reset(new TDataSource("mongodb://localhost:1235", "prod"));
    Server.reset(new httplib::Server());

    Server->Get("/api/admin/hi", [&](const httplib::Request& req, httplib::Response& res) {
        HiHandler(*DataSource, req, res);
    });
    Server->Get(R"(/api/admin/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        NumbersHandler(*DataSource, req, res);
    });

    Server->Post("/api/english/registration", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::RegistrationHandler(*DataSource, req, res);
    });
}

void TApplication::Start() {
    Cout << "Started HTTP-server" << Endl;
    Server->listen("0.0.0.0", 1234);
}

TApplication::~TApplication() {
    Server->stop();
    Cout << "Stopped HTTP-server" << Endl;
}
