#include "translations.h"

#include "english/handlers/pagination.h"
#include "english/handlers/common.h"

#include "english/collections/translation_collection.h"
#include "english/validators/admin/validator_translation.h"

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
        RestPutHandler<TCollectionTranslation, TValidatorTranslation>(
            dataSource.English.CollectionTranslation, req, response
        );
    }

    void GetAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler(dataSource.English.CollectionTranslation, req, response);
    }

    void GetAdminTranslationByFullMatchingHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& russian = req.GetParamValue("Russian", "");
        const TString& english = req.GetParamValue("English", "");
        
        const auto& record = dataSource.English.CollectionTranslation.FindByFullMatching(russian, english);
        if (record.has_value()) {
            response[RESPONSE_BODY] = record->ToJson();
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }

    void DeleteAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestDeleteHandler(dataSource, dataSource.English.CollectionTranslation, req, response);
    }

    void GetAdminTranslationsForAutoCompleteHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& name = req.GetParamValue("Name", "");
        response[RESPONSE_BODY] = NJson::TJsonValue::object();
        response[RESPONSE_BODY][RESPONSE_FIELD_RECORDS] = NJson::ToVectorJson(
            dataSource.English.CollectionTranslation.FindByWord(name, 10)
        );
    }

}
