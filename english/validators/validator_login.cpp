#include "validator_login.h"

#include "english/records/user_record.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    TValidatorLogin::TValidatorLogin(const NJson::TJsonValue& jsonData) {
        OriginJson = jsonData;
        IsValid = false;
    }

    bool TValidatorLogin::Validate(TDataSource& dataSource, TRecordUser* user) {
        IsValid = true;
        TMaybe<TRecordUser> foundUser = dataSource.English.CollectionUser.FindByEmail(
            OriginJson.value(RECORD_USER_FIELD_EMAIL, "")
        );

        Cout << "user id1-> " << foundUser->GetId() << Endl;
        Cout << "user id2-> " << foundUser->GetId() << Endl;

        ValidateRequired(RECORD_USER_FIELD_EMAIL);
        ValidateEmail(RECORD_USER_FIELD_EMAIL);
        ValidateEmailExists(foundUser);

        ValidateRequired(RECORD_USER_FIELD_PASSWORD);
        ValidateCorrectPassword(foundUser);

        Cout << "user id3-> " << foundUser->GetId() << Endl;
        if (foundUser) {
            *user = foundUser.value();
        }


        Cout << "user id-> " << user->GetId() << Endl;
        return IsValid;
    }

    void TValidatorLogin::ValidateEmailExists(TMaybe<TRecordUser>& user) {
        if (!user) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_EMAIL].push_back(VALIDATION_ERROR_NOT_FOUND);
        }
    }

    void TValidatorLogin::ValidateCorrectPassword(TMaybe<TRecordUser>& user) {
        if (user && !user->CheckPassword(OriginJson.value(RECORD_USER_FIELD_PASSWORD, ""))) {
            IsValid = false;
            ValidationErrors[RECORD_USER_FIELD_PASSWORD].push_back(VALIDATION_ERROR_INCORRECT);
        }
    }
}
