#pragma once

#include <iostream>

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "english/collections/user_collection.h"

namespace NEnglish {

    void RegistrationHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        try {
            TRecordUser user(NJson::TJsonValue::parse(req.body));
            NJson::TJsonValue result;
            if (user.IsValid(&result)) {
                if (dataSource.English.CollectionUser.IsAlreadyRegistred(user)) {
                    result["status"] = "user already register";
                } else {
                    if (!dataSource.English.CollectionUser.Register(user)) {
                        result["status"] = "insert error";
                    }
                }
            }
            std::cout << result.dump() << std::endl;
            res.set_content(result.dump(), "application/json");
        } catch (const std::exception& e) {
            NJson::TJsonValue result;
            result["status"] = e.what();
            std::cout << result << std::endl;
            res.set_content(result, "application/json");
        }
    }

}
