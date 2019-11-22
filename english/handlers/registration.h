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
        NJson::TJsonValue response;
        try {
            NJson::TJsonValue jsonUser = NJson::TJsonValue::parse(req.body);
            TValidatorUser validator(jsonUser);
            validator.AddExternalValidation(
                "Email",
                dataSource.English.CollectionUser.ExistsWithEmail(jsonUser.value("Email", "")),
                "AlreadyExists"
            );
            if (validator.Validate()) {
                if (!dataSource.English.CollectionUser.Register(TRecordUser(jsonUser))) {
                    response["Status"] = "InsertError";
                }
            } else {
                response = {
                    { "Status", "ValidationError", },
                    { "ValidationErrors", validator.GetValidationErrors() }
                };
            }
        } catch (const std::exception& e) {
            NJson::TJsonValue response;
            response["Status"] = "FatalError";
            response["Errors"] = e.what();
        }

        Cout << response.dump() << Endl;
        res.set_content(response.dump(), "application/json");
    }

}
