#include "application.h"

#include "contrib/json/json.h"

#include "sources/handlers/hi.h"
#include "sources/handlers/numbers.h"

#include "english/handlers/admin/sessions.h"
#include "english/handlers/login.h"
#include "english/handlers/users.h"

#include "util/generic/ctype.h"

TApplication::TApplication() {
    NJson::TJsonValue v;
    v["s"] = 123;
    Cout << NJson::GetString(v, "s", "") << Endl;
    Cout << NJson::GetInt(v, "s", 0) << Endl;
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
    Server->Post("/api/english/users", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::PostUserHandler(*DataSource, req, res);
    });
    Server->Get(R"(/api/english/users/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::GetUserHandler(*DataSource, req, res);
    });
    Server->Post("/api/english/login", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::PostLoginHandler(*DataSource, req, res);
    });
    Server->Get("/api/english/admin/sessions", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::GetAdminSessionsHandler(*DataSource, req, res);
    });
}
