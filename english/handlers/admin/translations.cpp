#pragma once

#include "english/handlers/pagination.h"
#include "english/handlers/common.h"

#include "english/collections/translation_collection.h"
#include "english/validators/validator_translation.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void GetAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler(dataSource.English.CollectionTranslation, req, response);
    }

    void PostAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionTranslation, TValidatorTranslation>(
            dataSource.English.CollectionTranslation, req, response
        );
    }

    void PutAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPutHandler<TCollectionTranslation, TRecordTranslation, TValidatorTranslation>(
            dataSource, dataSource.English.CollectionTranslation, req, response
        );
    }

    void GetAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler(dataSource.English.CollectionTranslation, req, response);
    }

    void DeleteAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestDeleteHandler(dataSource, dataSource.English.CollectionTranslation, req, response);
    }

}
