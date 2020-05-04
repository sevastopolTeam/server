#include "word_categories.h"

#include "english/collections/word_category_collection.h"
#include "english/records/word_category_record.h"
#include "english/validators/validator_word_category.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void GetAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler(dataSource.English.CollectionWordCategory, req, response);
    }

    void PostAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionWordCategory, TValidatorWordCategory>(
            dataSource.English.CollectionWordCategory, req, response
        );
    }

    void PutAdminWordCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPutHandler<TCollectionWordCategory, TValidatorWordCategory>(
            dataSource.English.CollectionWordCategory, req, response
        );
    }

    void GetAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler(dataSource.English.CollectionWordCategory, req, response);
    }

    void DeleteAdminWordCategoryHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestDeleteHandler(dataSource, dataSource.English.CollectionWordCategory, req, response);
    }

    void PostAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        // const NJson::TJsonValue& jsonTranslationCategory = NJson::TJsonValue::parse(req.body);
        // TValidatorTranslationToCategory validator(jsonWordCategory);
        // if (validator.Validate(dataSource)) {
        //     if (!dataSource.English.CollectionTranslationToCategory.Create(TRecordTranslationToCategory(jsonTranslationToCategory))) {
        //         response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
        //         response[RESPONSE_ERROR] = RESPONSE_ERROR_INSERT;
        //     }
        // } else {
        //     response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
        //     response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        // }
    }

}
