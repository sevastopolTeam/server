#include "translation_collection.h"

namespace NEnglish {
	bool TCollectionTranslation::ExistsByFullMatching(
        	const TString& valueFrom,
        	const TString& valueTo,
        	const TString& languageFrom,
        	const TString& languageTo
    ) {
        return Exists({
        	{ RECORD_TRANSLATION_FIELD_VALUE_FROM, valueFrom },
        	{ RECORD_TRANSLATION_FIELD_VALUE_TO, valueTo },
        	{ RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, languageFrom },
        	{ RECORD_TRANSLATION_FIELD_LANGUAGE_TO, languageTo }
        });
    }
}
