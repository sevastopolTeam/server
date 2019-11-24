#pragma once
#include "routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/user_collection.h"
#include "english/validators/validator_user.h"

#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    void RegistrationHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response;
        try {
            NJson::TJsonValue jsonUser = NJson::TJsonValue::parse(req.body);
            TValidatorUser validator(jsonUser);
            validator.AddExternalValidation(
                RECORD_USER_FIELD_EMAIL,
                dataSource.English.CollectionUser.ExistsWithEmail(jsonUser.value(RECORD_USER_FIELD_EMAIL, "")),
                VALIDATION_ERROR_ALREADY_EXISTS
            );
            if (validator.Validate()) {
                if (!dataSource.English.CollectionUser.Register(TRecordUser(jsonUser))) {
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
