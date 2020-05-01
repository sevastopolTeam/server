#pragma once

#include "contrib/httplib/httplib.h"

#include "english/collections/user_collection.h"
#include "english/collections/session_collection.h"
#include "english/records/user_record.h"
#include "english/records/session_record.h"

#include "util/generic/iostream.h"
#include "util/generic/maybe.h"
#include "util/generic/string.h"

#include "sources/data_source/data_source.h"

namespace NEnglish {

    using THandlerFn = std::function<void(TDataSource& dataSource, const httplib::Request&, NJson::TJsonValue&)>;

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

    void AdminHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res, const THandlerFn& handler)
    {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            if (IsAdmin(dataSource, req)) {
                handler(dataSource, req, response);
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

    void Handler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res, const THandlerFn& handler)
    {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        try {
            handler(dataSource, req, response);
            INFO_LOG << response.dump() << Endl;
        } catch (const std::exception& e) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_FATAL_ERROR;
            response[RESPONSE_ERROR] = e.what();
            ERROR_LOG << response.dump() << Endl;
        }

        res.set_content(response.dump(), RESPONSE_CONTENT_TYPE_JSON.c_str());
    }


    template <class TCollection, class TRecord, class TValidator>
    void RestGetHandler(TDataSource& dataSource, const httplib::Request& req, NJson::TJsonValue& response) {
        const TPagination pagination(req);
        response[RESPONSE_BODY] = {
            {
                TCollection::COLLECTION_NAME,
                NJson::ToVectorJson(
                    TCollection.Find(
                        NJson::TJsonValue::object(), pagination.skip, pagination.limit, {{RECORD_TRANSLATION_FIELD_FREQUENCY, -1}}
                    )
                )
            },
            {
                RESPONSE_FIELD_TRANSLATIONS_COUNT,
                dataSource.English.CollectionTranslation.Count()
            }
        };
    }

}
