#pragma once
#include "routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/user_collection.h"
#include "english/validators/validator_user.h"

#include "sources/data_source/data_source.h"
#include "sources/validators/validator.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    void GetUserHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            const TString& userId = req.matches[1];
            const TMaybe<TRecordUser>& record = dataSource.English.CollectionUser.FindById(userId);
            if (record.Empty()) {
                response[NEnglish::RESPONSE_STATUS] = VALIDATION_ERROR_NOT_FOUND;
            } else {
                response = record->ToJson();
            }
        } catch (std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << e.what() << Endl;
        }
        INFO_LOG << response << Endl;
        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

    void PostUserHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            NJson::TJsonValue jsonUser = NJson::TJsonValue::parse(req.body);
            TValidatorUser validator(jsonUser);
            if (validator.Validate(dataSource)) {
                if (!dataSource.English.CollectionUser.Create(TRecordUser(jsonUser))) {
                    response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                    response[RESPONSE_ERROR] = RESPONSE_ERROR_INSERT;
                }
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERRROR;
                response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
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
