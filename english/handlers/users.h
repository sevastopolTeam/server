#pragma once

#include "routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/user_collection.h"
#include "english/validators/validator_user.h"
#include "english/validators/validator_login.h"

#include "sources/data_source/data_source.h"
#include "sources/validators/validator.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    const TString RESPONSE_BODY_SESSION_TOKEN = "SessionToken";

    void GetUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetByIdHandler<TCollectionUser, TRecordUser>(
            dataSource, dataSource.English.CollectionUser, req, response
        );
    }

    void PostUserHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestPostHandler<TCollectionUser, TRecordUser, TValidatorUser>(
            dataSource, dataSource.English.CollectionUser, req, response
        );
    }

    void PostLoginHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        NJson::TJsonValue jsonLoginInfo = NJson::TJsonValue::parse(req.body);
        TValidatorLogin validator(jsonLoginInfo);
        TMaybe<TRecordUser> user = dataSource.English.CollectionUser.FindByEmail(
            NJson::GetString(jsonLoginInfo, RECORD_USER_FIELD_EMAIL, "")
        );
        if (validator.Validate(user)) {
            const TRecordSession& newSession(user->GetId());
            if (!dataSource.English.CollectionSession.Create(newSession)) {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_STATUS_ERROR] = RESPONSE_ERROR_INSERT;
            } else {
                response[RESPONSE_BODY] = {{RESPONSE_BODY_SESSION_TOKEN, newSession.GetToken()}};
            }
        } else {
            response = {
                { RESPONSE_STATUS, RESPONSE_STATUS_VALIDATION_ERROR },
                { RESPONSE_VALIDATION_ERRORS, validator.GetValidationErrors() }
            };
        }
    }

    void DeleteLogoutHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& authToken = req.GetHeaderValue(HEADERS_AUTHORIZATION);
        if (!dataSource.English.CollectionSession.RemoveByToken(authToken)) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_STATUS_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }
}
