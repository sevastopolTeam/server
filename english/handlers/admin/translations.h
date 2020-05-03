#pragma once

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"
#include "sources/data_source/data_source.h"

namespace NEnglish {
    void GetAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PostAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PutAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void GetAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void DeleteAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
}
