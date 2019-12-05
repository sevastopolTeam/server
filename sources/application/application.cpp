#include "application.h"

#include "contrib/json/json.h"

#include "sources/handlers/hi.h"
#include "sources/handlers/numbers.h"

#include "english/handlers/registration.h"

#include "english/handlers/login.h"
#include "english/handlers/admin/sessions.h"
#include "english/handlers/user.h"

TApplication::TApplication() {
    INFO_LOG << "Starting server..." << Endl;
    DataSource.reset(new TDataSource("mongodb://localhost:1235", "prod"));
    Server.reset(new httplib::Server());

    Server->Get("/api/admin/hi", [&](const httplib::Request& req, httplib::Response& res) {
        HiHandler(*DataSource, req, res);
    });
    Server->Get(R"(/api/admin/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        NumbersHandler(*DataSource, req, res);
    });

    AddEnglishHandlers();
}

void TApplication::Start() {
    INFO_LOG << "Started HTTP-server" << Endl;
    Server->listen("0.0.0.0", 1234);
}

TApplication::~TApplication() {
    Server->stop();
    INFO_LOG << "Stopped HTTP-server" << Endl;
}

void TApplication::AddEnglishHandlers() {
    Server->Post("/api/english/registration", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::RegistrationHandler(*DataSource, req, res);
    });

    Server->Post("/api/english/login", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::LoginHandler(*DataSource, req, res);
    });

    Server->Get("/api/english/admin/sessions", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminSessionsHandler(*DataSource, req, res);
    });

    Server->Post("/api/english/registration", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::RegistrationHandler(*DataSource, req, res);
    });
    Server->Get(R"(/api/english/user/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::UserHandler(*DataSource, req, res);
    });
}
