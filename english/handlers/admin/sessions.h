#pragma once
#include "english/handlers/routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/session_collection.h"

#include "sources/data_source/data_source.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

    void GetAdminSessionsHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (IsAdmin(currentUser)) {
                response[RESPONSE_BODY] = NJson::ToVectorJson(dataSource.English.CollectionSession.Find());
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_ACCESS_DENIED;
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
