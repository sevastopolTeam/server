#pragma once
#include "routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/user_collection.h"

#include "sources/data_source/data_source.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void UserHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response;
        try {
            TString userId = req.matches[1];
            TMaybe<NJson::TJsonValue> record = dataSource.English.CollectionUser.Find(userId);
            if (!record) {
                response = { { NEnglish::RESPONSE_STATUS, "user not found" } };
            } else {
                response = *record.Get();
            }
        } catch (std::exception& e) {
            response = { { NEnglish::RESPONSE_STATUS, e.what() } };
            ERROR_LOG << e.what() << Endl;
        }
        INFO_LOG << response << Endl;
        res.set_content(response.dump(), "text/plain");
    }

}
