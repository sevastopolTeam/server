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

    const TString RESPONSE_FIELD_WORD_CATEGORIES = "WordCategories";
    const TString RESPONSE_FIELD_WORD_CATEGORIES_COUNT = "WordCategoriesCount";

    void GetAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TPagination pagination(req);
        response[RESPONSE_BODY] = {
            {
                RESPONSE_FIELD_WORD_CATEGORIES,
                NJson::ToVectorJson(
                    dataSource.English.CollectionWordCategory.Find(NJson::TJsonValue::object(), pagination.skip, pagination.limit)
                )
            },
            {
                RESPONSE_FIELD_WORD_CATEGORIES_COUNT,
                dataSource.English.CollectionWordCategory.Count()
            }
        };
    }

    void PostAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
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
    }

    void PutAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const NJson::TJsonValue& jsonWordCategory = NJson::TJsonValue::parse(req.body);
        TValidatorWordCategory validator(jsonWordCategory);
        if (validator.Validate(dataSource)) {
            dataSource.English.CollectionWordCategory.FindByIdAndModify(
                NJson::GetString(jsonWordCategory, RECORD_FIELD_ID, ""), TRecordWordCategory(jsonWordCategory));
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
            response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        }
    }

    void GetAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& wordCategoryId = req.matches[1];
        const auto& wordCategory = dataSource.English.CollectionWordCategory.FindById(wordCategoryId);
        if (wordCategory.has_value()) {
            response[RESPONSE_BODY] = wordCategory->ToJson();
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }

    void DeleteAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& wordCategoryId = req.matches[1];
        const bool isSuccess = dataSource.English.CollectionWordCategory.RemoveById(wordCategoryId);
        if (!isSuccess) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }

}
