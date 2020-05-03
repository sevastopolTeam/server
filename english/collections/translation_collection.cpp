#include "translation_collection.h"

#include "contrib/json/json.h"

namespace NEnglish {
	TMaybe<TRecordTranslation> TCollectionTranslation::FindByFullMatching(
        	const TString& valueFrom,
        	const TString& valueTo,
        	const TString& languageFrom,
        	const TString& languageTo
    ) {
        return FindFirst({
        	{ RECORD_TRANSLATION_FIELD_VALUE_FROM, valueFrom },
        	{ RECORD_TRANSLATION_FIELD_VALUE_TO, valueTo },
        	{ RECORD_TRANSLATION_FIELD_LANGUAGE_FROM, languageFrom },
        	{ RECORD_TRANSLATION_FIELD_LANGUAGE_TO, languageTo }
        });
    }

}
