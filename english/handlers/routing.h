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
    const TString RESPONSE_STATUS_VALIDATION_ERROR = "ValidationError";
    const TString RESPONSE_STATUS_FATAL_ERROR = "FatalError";

    const TString RESPONSE_ERROR_INSERT = "InsertError";
    const TString RESPONSE_ERROR_ACCESS_DENIED = "AccessDenied";
    const TString RESPONSE_ERROR_NOT_FOUND = "NotFound";

    const TString RESPONSE_CONTENT_TYPE_JSON = "application/json";

    TMaybe<TRecordUser> GetCurrentUser(TDataSource& dataSource, const httplib::Request& req) {
        const TString authToken = req.GetHeaderValue(HEADERS_AUTHORIZATION);
        const TMaybe<TRecordSession>& session = dataSource.English.CollectionSession.FindByToken(authToken);
        if (!session) {
            return Nothing();
        }

        return dataSource.English.CollectionUser.FindById(session->GetUserId());
    }

    bool IsRegisteredUser(const TMaybe<TRecordUser>& user) {
        return !!user;
    }

    bool IsAdminUser(const TMaybe<TRecordUser>& user) {
        return !!user && user->IsAdmin();
    }

    bool IsAdmin(TDataSource& dataSource, const httplib::Request& req) {
        const TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
        return IsAdminUser(currentUser);
    }

    bool IsRegistered(TDataSource& dataSource, const httplib::Request& req) {
        const TMaybe<TRecordUser> currentUser = GetCurrentUser(dataSource, req);
        return IsRegisteredUser(currentUser);
    }

}
