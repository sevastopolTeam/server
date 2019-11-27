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

    void AdminSessionsHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response;
        try {

            std::time_t nowTime = time(NULL);
            Cout << NString::ToString(nowTime) << Endl;

            Cout << "Headers" << Endl;
            // Cout << req.headers["Authoriation"] << Endl;
            for (auto& p: req.headers) {
                Cout << p.first << " " << p.second << Endl;
            }
            const auto& sessions = dataSource.English.CollectionSession.Find();
            response["sessions"] = {};
            for (const auto& session: sessions) {
                response["sessions"].push_back(session.ToJson());
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
