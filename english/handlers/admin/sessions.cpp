#include "sessions.h"

#include "english/handlers/common.h"
#include "english/collections/session_collection.h"

namespace NEnglish {

    void GetAdminSessionsHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        RestGetHandler(dataSource.English.CollectionSession, req, response);
    }

}
