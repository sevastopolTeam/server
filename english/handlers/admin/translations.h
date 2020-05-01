#pragma once

#include "english/handlers/pagination.h"
#include "english/handlers/routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/translation_collection.h"
#include "english/validators/validator_translation.h"

#include "sources/data_source/data_source.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void GetAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler<TCollectionTranslation, TRecordTranslation>(
            dataSource, dataSource.English.CollectionTranslation, req, response
        );
    }

    void PostAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionTranslation, TRecordTranslation, TValidatorTranslation>(
            dataSource, dataSource.English.CollectionTranslation, req, response
        );
    }

    void PutAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPutHandler<TCollectionTranslation, TRecordTranslation, TValidatorTranslation>(
            dataSource, dataSource.English.CollectionTranslation, req, response
        );
    }

    void GetAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler<TCollectionTranslation, TRecordTranslation>(
            dataSource, dataSource.English.CollectionTranslation, req, response
        );
    }

    void DeleteAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestDeleteHandler<TCollectionTranslation, TRecordTranslation>(
            dataSource, dataSource.English.CollectionTranslation, req, response
        );
    }

}
