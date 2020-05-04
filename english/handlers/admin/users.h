#pragma once

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"
#include "sources/data_source/data_source.h"

namespace NEnglish {
    void GetAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PostAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PutAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void GetAdminUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void DeleteAdminUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
}