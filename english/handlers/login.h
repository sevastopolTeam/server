#pragma once
#include "routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/session_collection.h"
#include "english/collections/user_collection.h"
#include "english/records/session_record.h"
#include "english/records/user_record.h"
#include "english/validators/validator_login.h"

#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    void LoginHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response;
        try {
            NJson::TJsonValue jsonLoginInfo = NJson::TJsonValue::parse(req.body);
            TValidatorLogin validator(jsonLoginInfo);
            const TRecordUser* user = dataSource.English.CollectionUser.FindByEmail(
                jsonLoginInfo.value(RECORD_USER_FIELD_EMAIL, "")
            );
            
            validator.Validate();
            validator.AddExternalValidation(
                RECORD_USER_FIELD_EMAIL,
                user == nullptr,
                VALIDATION_ERROR_NOT_EXISTS
            );
            validator.AddExternalValidation(
                RECORD_USER_FIELD_PASSWORD,
                user != nullptr && user->CheckPassword(jsonLoginInfo.value("Password", "")),
                VALIDATION_ERROR_INCORRECT
            );
            if (validator.IsValid()) {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_OK;
                if (!dataSource.English.CollectionSession.Create(TRecordSession(user->GetId()))) {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_INSERT_ERROR;
                } else {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_OK;
                }
            } else {
                response = {
                    { RESPONSE_STATUS, RESPONSE_STATUS_VALIDATION_ERRROR },
                    { RESPONSE_VALIDATION_ERRORS, validator.GetValidationErrors() }
                };
            }
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERRORS] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }
        res.set_content(response.dump(), "application/json");
    }

}
