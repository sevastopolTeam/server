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

    const TString RESPONSE_FIELD_TRANSLATIONS = "Translations";
    const TString RESPONSE_FIELD_TRANSLATIONS_COUNT = "TranslationsCount";

    void GetAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TPagination pagination(req);
        response[RESPONSE_BODY] = {
            {
                RESPONSE_FIELD_TRANSLATIONS,
                NJson::ToVectorJson(
                    dataSource.English.CollectionTranslation.Find(
                        NJson::TJsonValue::object(), pagination.skip, pagination.limit, {{RECORD_TRANSLATION_FIELD_FREQUENCY, -1}}
                    )
                )
            },
            {
                RESPONSE_FIELD_TRANSLATIONS_COUNT,
                dataSource.English.CollectionTranslation.Count()
            }
        };
    }

    void PostAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const NJson::TJsonValue& jsonTranslation = NJson::TJsonValue::parse(req.body);
        TValidatorTranslation validator(jsonTranslation);
        if (validator.Validate(dataSource)) {
            const TMaybe<TRecordTranslation> createdTranslation
                = dataSource.English.CollectionTranslation.CreateAndReturn(TRecordTranslation(jsonTranslation));
            if (createdTranslation.has_value()) {
                response[RESPONSE_BODY] = createdTranslation->GetId();
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_INSERT;
            }
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
            response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        }
    }

    void PutAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const NJson::TJsonValue& jsonTranslation = NJson::TJsonValue::parse(req.body);
        TValidatorTranslation validator(jsonTranslation);
        if (validator.Validate(dataSource)) {
            const TString& recordId = NJson::GetString(jsonTranslation, RECORD_TRANSLATION_FIELD_ID, "");
            dataSource.English.CollectionTranslation.FindByIdAndModify(recordId , TRecordTranslation(jsonTranslation));
            response[RESPONSE_BODY] = recordId;
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
            response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        }
    }

    void GetAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& translationId = req.matches[1];
        const auto& translation = dataSource.English.CollectionTranslation.FindById(translationId);
        if (translation.has_value()) {
            response[RESPONSE_BODY] = translation->ToJson();
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }

    void DeleteAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& translationId = req.matches[1];
        const bool isSuccess = dataSource.English.CollectionTranslation.RemoveById(translationId);
        if (!isSuccess) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }

}
