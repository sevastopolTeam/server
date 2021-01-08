#include "validator_translation_to_category.h"

#include "sources/data_source/data_source.h"
#include "english/records/translation_to_category_record.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    TValidatorTranslationToCategory::TValidatorTranslationToCategory(const NJson::TJsonValue& jsonData)
        : IValidatorCommonEnglish(jsonData) {}

    bool TValidatorTranslationToCategory::Validate(TCollectionTranslationToCategory& collection) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID);
        isValid &= ValidateExistingTranslationId(collection);

        isValid &= ValidateRequired(RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID);
        isValid &= ValidateExistingWordCategoryId(collection);

        isValid &= ValidateExists(collection);
        return static_cast<bool>(isValid);
    }

    bool TValidatorTranslationToCategory::ValidateExistingTranslationId(TCollectionTranslationToCategory& collection) {
        const TString& id = NJson::GetString(OriginJson, RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID, "");
        if (id.size() == 0) {
            return true;
        }
        const auto foundRecord = collection.DataSource->English.CollectionTranslation.FindById(id);
        if (!foundRecord.has_value()) {
            ValidationErrors[RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID].push_back(VALIDATION_ERROR_NOT_FOUND);
            return false;
        }

        return true;
    }

    bool TValidatorTranslationToCategory::ValidateExistingWordCategoryId(TCollectionTranslationToCategory& collection) {
        const TString& id = NJson::GetString(OriginJson, RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, "");
        if (id.size() == 0) {
            return true;
        }        
        const auto foundRecord = collection.DataSource->English.CollectionWordCategory.FindById(id);
        if (!foundRecord) {
            ValidationErrors[RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID].push_back(VALIDATION_ERROR_NOT_FOUND);
            return false;
        }

        return true;
    }

    bool TValidatorTranslationToCategory::ValidateExists(TCollectionTranslationToCategory& collection) {
        const auto foundRecord = collection.FindByFullMatching(
            NJson::GetString(OriginJson, RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID, ""),
            NJson::GetString(OriginJson, RECORD_TRANSLATION_TO_CATEGORY_FIELD_WORD_CATEGORY_ID, "")
        );

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_FIELD_ID, "")) {
            ValidationErrors[RECORD_TRANSLATION_TO_CATEGORY_FIELD_TRANSLATION_ID].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }
}