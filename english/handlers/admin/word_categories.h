#pragma once

#include "english/handlers/common.h"
#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"
#include "sources/data_source/data_source.h"

namespace NEnglish {
    void GetAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PostAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PutAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void GetAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void DeleteAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void GetAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PostAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
    void PutAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response);
}
