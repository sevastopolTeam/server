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
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
            Cout << currentUser.Empty() << Endl;
            if (!currentUser.Empty()) {
                Cout << currentUser->ToJson() << Endl;
            }
            if (IsAdmin(currentUser)) {
                NJson::TJsonValue jsonSessions;
                const TVector<TRecordSession>& sessions = dataSource.English.CollectionSession.Find();
                for (const auto& session: sessions) {
                    jsonSessions.push_back(session.ToJson());
                }
                response[RESPONSE_BODY] = jsonSessions;
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
