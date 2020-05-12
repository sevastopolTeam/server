#include "validator_admin_user.h"

#include "english/records/user_record.h"

namespace NEnglish {

    TValidatorAdminUser::TValidatorAdminUser(const NJson::TJsonValue& jsonData): IValidatorCommonEnglish(jsonData) {}

    bool TValidatorAdminUser::Validate(TCollectionUser& userCollection) {
        int isValid = 1;
        isValid &= ValidateRequired(RECORD_USER_FIELD_NAME);

        isValid &= ValidateRequired(RECORD_USER_FIELD_EMAIL);
        isValid &= ValidateEmail(RECORD_USER_FIELD_EMAIL);
        isValid &= ValidateExists(userCollection);

        isValid &= ValidateRequired(RECORD_USER_FIELD_PHONE);
        isValid &= ValidatePhone(RECORD_USER_FIELD_PHONE);

        isValid &= ValidateSame(RECORD_USER_FIELD_REPEAT_PASSWORD, RECORD_USER_FIELD_PASSWORD);

        return static_cast<bool>(isValid);
    }

    bool TValidatorAdminUser::ValidateExists(TCollectionUser& collectionUser) {
        const auto foundRecord = collectionUser.FindByEmail(NJson::GetString(OriginJson, RECORD_USER_FIELD_EMAIL, ""));

        if (foundRecord && foundRecord->GetId() != NJson::GetString(OriginJson, RECORD_FIELD_ID, "")) {
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_ALREADY_EXISTS);
            return false;
        }

        return true;
    }

}
