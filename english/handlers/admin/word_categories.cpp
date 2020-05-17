#include "word_categories.h"

#include "english/collections/word_category_collection.h"
#include "english/validators/admin/validator_word_category.h"

#include "english/collections/translation_to_category_collection.h"
#include "english/validators/admin/validator_translation_to_category.h"

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


    void GetAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler(dataSource.English.CollectionTranslationToCategory, req, response);
    }

    void PostAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionTranslationToCategory, TValidatorTranslationToCategory>(
            dataSource.English.CollectionTranslationToCategory, req, response
        );
    }

    void PutAdminTranslationToCategoriesHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPutHandler<TCollectionTranslationToCategory, TValidatorTranslationToCategory>(
            dataSource.English.CollectionTranslationToCategory, req, response
        );
    }

}
