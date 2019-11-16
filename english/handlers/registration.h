#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "english/collections/user_collection.h"

#include "util/generic/iostream.h"

namespace NEnglish {

    void RegistrationHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        try {
            TRecordUser user(NJson::TJsonValue::parse(req.body));
            NJson::TJsonValue result;
            if (user.IsValide(&result)) {
                if (dataSource.English.CollectionUser.IsAlreadyRegistred(user)) {
                    result["status"] = "user already register";
                } else {
                    if (!dataSource.English.CollectionUser.Register(user)) {
                        result["status"] = "insert error";
                    }
                }
            }
            Cout << result.dump() << Endl;
            res.set_content(result.dump(), "application/json");
        } catch (const std::exception& e) {
            NJson::TJsonValue result;
            result["status"] = e.what();
            Cout << result << Endl;
            res.set_content(result, "application/json");
        }
    }

}
