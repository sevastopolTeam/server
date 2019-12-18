#include "application.h"

#include "contrib/json/json.h"

#include "sources/handlers/hi.h"
#include "sources/handlers/numbers.h"

#include "english/handlers/registration.h"
#include "english/handlers/user.h"

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

    Server->Post("/api/english/registration", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::RegistrationHandler(*DataSource, req, res);
    });
    Server->Get(R"(/api/english/user/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::UserHandler(*DataSource, req, res);
    });
}

void TApplication::Start() {
    INFO_LOG << "Started HTTP-server" << Endl;
    Server->listen("0.0.0.0", 1234);
}

TApplication::~TApplication() {
    Server->stop();
    INFO_LOG << "Stopped HTTP-server" << Endl;
}
