#include "users.h"

#include "english/handlers/common.h"
#include "english/collections/user_collection.h"
#include "english/validators/admin/validator_admin_user.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void GetAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler(dataSource.English.CollectionUser, req, response);
    }

    void PostAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionUser, TValidatorAdminUser>(
            dataSource.English.CollectionUser, req, response
        );
    }

    void PutAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        auto& collection = dataSource.English.CollectionUser;
        const NJson::TJsonValue& jsonRecord = NJson::TJsonValue::parse(req.body);
        TValidatorAdminUser validator(jsonRecord);
        if (validator.Validate(collection)) {
            const TString& recordId = NJson::GetString(jsonRecord, RECORD_FIELD_ID, "");
            auto user = collection.FindById(recordId);
            user->UpdateAdminFields(jsonRecord);
            collection.FindByIdAndModify(recordId, user.value());
            response[RESPONSE_BODY] = {{ RECORD_FIELD_ID, recordId }};
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
            response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        }
    }

    void GetAdminUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler(dataSource.English.CollectionUser, req, response);
    }

    void DeleteAdminUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestDeleteHandler(dataSource, dataSource.English.CollectionUser, req, response);
    }

}
