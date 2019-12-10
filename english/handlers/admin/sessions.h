#pragma once
#include "english/handlers/routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/session_collection.h"

#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

#include <ctime>
#include <util/generic/string.h>

namespace NEnglish {

    void GetAdminSessionsHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response;
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            if (currentUser.Empty()) {
                Cout << "Empty" << Endl;
            } else {
                Cout << currentUser->ToJson() << Endl;
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
