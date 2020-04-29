#include "application.h"

#include "contrib/json/json.h"

#include "sources/handlers/hi.h"
#include "sources/handlers/numbers.h"

#include "english/handlers/routing.h"

#include "english/handlers/admin/sessions.h"
#include "english/handlers/admin/translations.h"
#include "english/handlers/admin/word_categories.h"
#include "english/handlers/users.h"

#include "util/generic/ctype.h"

TApplication::TApplication(NJson::TJsonValue& config)
    : Config(config)
{
    INFO_LOG << "Starting server..." << Endl;
    DataSource.reset(new TDataSource(Config["Server"]["MongoUri"], Config["Server"]["MongoDbName"]));
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
    INFO_LOG << "Started HTTP-server on port: " << Config["Server"]["Port"] << Endl;
    Server->listen("0.0.0.0", Config["Server"]["Port"]);
}

TApplication::~TApplication() {
    Server->stop();
    INFO_LOG << "Stopped HTTP-server" << Endl;
}

void TApplication::AddEnglishHandlers() {
    Server->Post("/api/english/users", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::Handler(*DataSource, req, res, NEnglish::PostUserHandler);
    });
    Server->Get(R"(/api/english/users/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::Handler(*DataSource, req, res, NEnglish::GetUserHandler);
    });
    Server->Post("/api/english/login", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::Handler(*DataSource, req, res, NEnglish::PostLoginHandler);
    });
    Server->Delete("/api/english/logout", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::Handler(*DataSource, req, res, NEnglish::DeleteLogoutHandler);
    });
    Server->Get("/api/english/admin/sessions", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::GetAdminSessionsHandler);
    });

    Server->Post("/api/english/admin/translations", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::PostAdminTranslationsHandler);
    });
    Server->Put("/api/english/admin/translations", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::PutAdminTranslationsHandler);
    });
    Server->Get("/api/english/admin/translations", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::GetAdminTranslationsHandler);
    });
    Server->Get(R"(/api/english/admin/translations/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::GetAdminTranslationHandler);
    });
    Server->Delete(R"(/api/english/admin/translations/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::DeleteAdminTranslationHandler);
    });
    Server->Post("/api/english/admin/word_categories", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::PostAdminWordCategoriesHandler);
    });
    Server->Put("/api/english/admin/word_categories", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::PutAdminWordCategoriesHandler);
    });
    Server->Get("/api/english/admin/word_categories", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::GetAdminWordCategoriesHandler);
    });
    Server->Get(R"(/api/english/admin/word_categories/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::GetAdminWordCategoryHandler);
    });
    Server->Delete(R"(/api/english/admin/word_categories/([a-zA-Z0-9]+))", [&](const httplib::Request& req, httplib::Response& res) {
        NEnglish::AdminHandler(*DataSource, req, res, NEnglish::DeleteAdminWordCategoryHandler);
    });
    
}
