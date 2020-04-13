#pragma once

#include "english/handlers/routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/word_category_collection.h"
#include "english/records/word_category_record.h"
#include "english/validators/validator_word_category.h"

#include "sources/data_source/data_source.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    const TString WORD_CATEGORIES_SIZE_OF_PAGE_PARAM = "PageSize";
    const TString WORD_CATEGORIES_NUMBER_OF_PAGE_PARAM = "Page";

    const TString RESPONSE_FIELD_WORD_CATEGORIES = "WordCategories";
    const TString RESPONSE_FIELD_WORD_CATEGORIES_COUNT = "WordCategoriesCount";

    void GetAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            if (IsAdmin(dataSource, req)) {
                const int limit = NType::ToInt(req.GetParamValue(WORD_CATEGORIES_SIZE_OF_PAGE_PARAM, "0"));
                const int skip = NType::ToInt(req.GetParamValue(WORD_CATEGORIES_NUMBER_OF_PAGE_PARAM, "0")) * limit;
                response[RESPONSE_BODY] = {
                    {
                        RESPONSE_FIELD_WORD_CATEGORIES,
                        NJson::ToVectorJson(
                            dataSource.English.CollectionWordCategory.Find(NJson::TJsonValue::object(), skip, limit)
                        )
                    },
                    {
                        RESPONSE_FIELD_WORD_CATEGORIES_COUNT,
                        dataSource.English.CollectionWordCategory.Count()
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

    void PostAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            if (IsAdmin(dataSource, req)) {
                const NJson::TJsonValue& jsonWordCategory = NJson::TJsonValue::parse(req.body);
                TValidatorWordCategory validator(jsonWordCategory);
                if (validator.Validate(dataSource)) {
                    if (!dataSource.English.CollectionWordCategory.Create(TRecordWordCategory(jsonWordCategory))) {
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

    void PutAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            if (IsAdmin(dataSource, req)) {
                const NJson::TJsonValue& jsonWordCategory = NJson::TJsonValue::parse(req.body);
                TValidatorWordCategory validator(jsonWordCategory);
                if (validator.Validate(dataSource)) {
                    dataSource.English.CollectionWordCategory.FindByIdAndModify(
                        NJson::GetString(jsonWordCategory, RECORD_FIELD_ID, ""), TRecordWordCategory(jsonWordCategory));
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

    void GetAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            if (IsAdmin(dataSource, req)) {
                const TString& wordCategoryId = req.matches[1];
                const auto& wordCategory = dataSource.English.CollectionWordCategory.FindById(wordCategoryId);
                if (wordCategory.has_value()) {
                    response[RESPONSE_BODY] = wordCategory->ToJson();
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

    void DeleteAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            if (IsAdmin(dataSource, req)) {
                const TString& wordCategoryId = req.matches[1];
                const bool isSuccess = dataSource.English.CollectionWordCategory.RemoveById(wordCategoryId);
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
