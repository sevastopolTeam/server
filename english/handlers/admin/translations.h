#pragma once

#include <limits>

#include "english/handlers/routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/translation_collection.h"
#include "english/validators/validator_translation.h"

#include "sources/data_source/data_source.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    const TString SIZE_OF_PAGE_PARAM = "PageSize";
    const TString NUMBER_OF_PAGE_PARAM = "Page";

    void GetAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (IsAdmin(currentUser)) {
                int limit = NType::ToInt(req.GetParamValue(SIZE_OF_PAGE_PARAM, "0"));
                int skip = NType::ToInt(req.GetParamValue(NUMBER_OF_PAGE_PARAM, "0")) * limit;
                response[RESPONSE_BODY] = {
                    {
                        "Translations",
                        NJson::ToVectorJson(
                            dataSource.English.CollectionTranslation.Find(NJson::TJsonValue::object(), skip, limit)
                        )
                    },
                    {
                        "TranslationsCount",
                        dataSource.English.CollectionTranslation.All().size()
                    }
                };
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_ACCESS_DENIED;
            }
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }

        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

    void PostAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (IsAdmin(currentUser)) {
                const NJson::TJsonValue& jsonTranslation = NJson::TJsonValue::parse(req.body);
                TValidatorTranslation validator(jsonTranslation);
                if (validator.Validate(dataSource)) {
                    if (!dataSource.English.CollectionTranslation.Create(TRecordTranslation(jsonTranslation))) {
                        response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                        response[RESPONSE_ERROR] = RESPONSE_ERROR_INSERT;
                    }
                } else {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
                    response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
                }
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_ACCESS_DENIED;
            }
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }
        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

    void PutAdminTranslationsHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (IsAdmin(currentUser)) {
                const NJson::TJsonValue& jsonTranslation = NJson::TJsonValue::parse(req.body);
                TValidatorTranslation validator(jsonTranslation);
                if (validator.Validate(dataSource)) {
                    dataSource.English.CollectionTranslation.FindByIdAndModify(
                        NJson::GetString(jsonTranslation["Id"], ""), TRecordTranslation(jsonTranslation));
                } else {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
                    response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
                }
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_ACCESS_DENIED;
            }
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }
        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

    void GetAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (IsAdmin(currentUser)) {
                const TString& translationId = req.matches[1];
                const auto& translation = dataSource.English.CollectionTranslation.FindById(translationId);
                if (translation.has_value()) {
                    response[RESPONSE_BODY] = translation->ToJson();
                } else {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                    response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
                }
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_ACCESS_DENIED;
            }
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }

        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

    void DeleteAdminTranslationHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (IsAdmin(currentUser)) {
                const TString& translationId = req.matches[1];
                const bool isSuccess = dataSource.English.CollectionTranslation.RemoveById(translationId);
                if (!isSuccess) {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                    response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
                }
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_ACCESS_DENIED;
            }
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }

        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

}
