#pragma once

#include "contrib/httplib/httplib.h"

#include "english/collections/user_collection.h"
#include "english/collections/session_collection.h"
#include "english/records/user_record.h"
#include "english/records/session_record.h"

#include "util/generic/string.h"
#include "util/generic/maybe.h"

namespace NEnglish {
    const TString HEADERS_AUTHORIZATION = "Authorization";

    const TString RESPONSE_STATUS = "Status";
    const TString RESPONSE_VALIDATION_ERRORS = "ValidationErrors";
    const TString RESPONSE_ERROR = "Error";
    const TString RESPONSE_BODY = "Body";

    const TString RESPONSE_STATUS_OK = "Ok";
    const TString RESPONSE_STATUS_ERROR = "Error";
    const TString RESPONSE_STATUS_VALIDATION_ERRROR = "ValidationError";
    const TString RESPONSE_STATUS_FATAL_ERROR = "FatalError";

    const TString RESPONSE_ERROR_INSERT = "InsertError";
    const TString RESPONSE_ERROR_ACCESS_DENIED = "AccessDenied";

    const TString RESPONSE_CONTENT_TYPE_JSON = "application/json";

    TMaybe<TRecordUser> GetCurrentUser(TDataSource& dataSource, const httplib::Request& req) {
        const auto it = req.headers.find(HEADERS_AUTHORIZATION);
        if (it == req.headers.end()) {
            return Nothing();
        }

        Cout << "headers" << it->second << Endl;

        const TString authToken = it->second;
        const TMaybe<TRecordSession>& session = dataSource.English.CollectionSession.FindByToken(authToken);
        if (!session.has_value()) {
            Cout << "Empty()" << Endl;
            return Nothing();
        }

        Cout << "session " << session->GetUserId() << Endl;

        return dataSource.English.CollectionUser.FindById(session->GetUserId());
    }

    bool IsRegistered(const TMaybe<TRecordUser>& user) {
        return !!user;
    }

    bool IsAdmin(const TMaybe<TRecordUser>& user) {
        return !!user && user->IsAdmin();
    }

}
