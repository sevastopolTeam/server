#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

namespace NEnglish {

    const TString RESPONSE_BODY_SESSION_TOKEN = "SessionToken";

    void GetUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PostUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PostLoginHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void DeleteLogoutHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
}
