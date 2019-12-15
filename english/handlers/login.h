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
    const TString RESPONSE_BODY_SESSION_TOKEN = "SessionToken";

    void PostLoginHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            NJson::TJsonValue jsonLoginInfo = NJson::TJsonValue::parse(req.body);
            TValidatorLogin validator(jsonLoginInfo);
            TRecordUser user;
            if (validator.Validate(dataSource, &user)) {
                const TRecordSession& newSession(user.GetId());
                Cout << "userId " << user.GetId() << Endl;
                if (!dataSource.English.CollectionSession.Create(newSession)) {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                    response[RESPONSE_STATUS_ERROR] = RESPONSE_ERROR_INSERT;
                } else {
                    response[RESPONSE_BODY] = {{RESPONSE_BODY_SESSION_TOKEN, newSession.GetToken()}};
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
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }
        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

}
