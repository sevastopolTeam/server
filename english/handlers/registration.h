#pragma once

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"
#include "sources/data_source/data_source.h"

#include "english/collections/user_collection.h"

#include "util/generic/iostream.h"

#include "english/validators/validator_user.h"
#include "sources/records/base_record.h"

#include <string>

namespace NEnglish {

    void RegistrationHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        try {
            NJson::TJsonValue jsonUser = NJson::TJsonValue::parse(req.body);
            TValidatorUser validator(jsonUser);

            if (dataSource.English.CollectionUser.ExistsWithEmail(jsonUser.value("Email", ""))) {
                validator.AddValidationError("Email", "already_exists");
            }

            if (validator.Validate()) {
                if (!dataSource.English.CollectionUser.Register(TRecordUser(jsonUser))) {
                    response["status"] = "insert_error";
                }
            } else {
                response = {
                    { "status", "validation_error", },
                    { "validation_errors", validator.GetValidationErrors() }
                };
            }
        } catch (const std::exception& e) {
            NJson::TJsonValue response;
            response["status"] = "fatal_error";
            response["error"] = e.what();
        }

        Cout << response.dump() << Endl;
        res.set_content(response.dump(), "application/json");
    }

}
