#pragma once
#include "routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/user_collection.h"

#include "sources/data_source/data_source.h"
#include "sources/validators/validator.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void UserHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response;
        try {
            const TString& userId = req.matches[1];
            const TMaybe<TRecordUser>& record = dataSource.English.CollectionUser.FindById(userId);
            if (record.Empty()) {
                response = {{ NEnglish::RESPONSE_STATUS, VALIDATION_ERROR_NOT_FOUND }};
            } else {
                response = record->ToJson();
            }
        } catch (std::exception& e) {
            response = {{ NEnglish::RESPONSE_STATUS, e.what() }};
            ERROR_LOG << e.what() << Endl;
        }
        INFO_LOG << response << Endl;
        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }

}
