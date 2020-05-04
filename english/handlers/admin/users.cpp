#include "users.h"

#include "english/handlers/common.h"
#include "english/collections/user_collection.h"
#include "english/validators/validator_user.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void GetAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler(dataSource.English.CollectionUser, req, response);
    }

    void PostAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionUser, TValidatorUser>(
            dataSource.English.CollectionUser, req, response
        );
    }

    void PutAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPutHandler<TCollectionUser, TValidatorUser>(
            dataSource.English.CollectionUser, req, response
        );
    }

    void GetAdminUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler(dataSource.English.CollectionUser, req, response);
    }

    void DeleteAdminUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestDeleteHandler(dataSource, dataSource.English.CollectionUser, req, response);
    }

}