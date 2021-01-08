#include "word_categories.h"

#include "english/collections/translation_collection.h"

#include "english/collections/word_category_collection.h"
#include "english/validators/admin/validator_word_category.h"

#include "english/collections/translation_to_category_collection.h"
#include "english/validators/admin/validator_translation_to_category.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"
#include "util/generic/hashmap.h"

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
        const TString& recordId = req.GetParamValue(RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, "");
        const auto& categoryTranslations = dataSource.English.CollectionTranslationToCategory.FindByWordCategoryId(recordId);
        NJson::TJsonValue ids = NJson::TJsonValue::array();
        for (const auto& c: categoryTranslations) {
            ids.push_back({{ "$oid", c.GetTranslationId() }});
        }
        const auto& translations = dataSource.English.CollectionTranslation.Find({{ "_id", {{ "$in",  ids }} }});
        THashMap<TString, TRecordTranslation> idToTranslation;
        for (const auto& t: translations) {
            idToTranslation[t.GetId()] = t;
        }

        NJson::TJsonValue categoriesWithTranslations = NJson::TJsonValue::array();        
        for (auto& c: categoryTranslations) {
            categoriesWithTranslations.push_back({
                { "TranslationToCategory", c.ToJson() },
                { "Translation", idToTranslation[c.GetTranslationId()].ToJson() }
            });
        }

        response[RESPONSE_BODY] = {{ "Records", categoriesWithTranslations }};
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
