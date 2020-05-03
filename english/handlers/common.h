#pragma once

#include "contrib/httplib/httplib.h"

#include "english/handlers/pagination.h"
#include "english/collections/user_collection.h"
#include "english/records/user_record.h"

#include "util/generic/iostream.h"
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

    const TString RESPONSE_FIELD_RECORDS = "Records";
    const TString RESPONSE_FIELD_RECORDS_COUNT = "RecordsCount";

    TMaybe<TRecordUser> GetCurrentUser(TDataSource& dataSource, const httplib::Request& req);
    bool IsRegisteredUser(const TMaybe<TRecordUser>& user);
    bool IsAdminUser(const TMaybe<TRecordUser>& user);
    bool IsAdmin(TDataSource& dataSource, const httplib::Request& req);
    bool IsRegistered(TDataSource& dataSource, const httplib::Request& req);
    void AdminHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res, const THandlerFn& handler);
    void Handler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res, const THandlerFn& handler);

    template <class TCollection>
    void RestGetHandler(TCollection& collection, const httplib::Request& req, NJson::TJsonValue& response) {
        const TPagination pagination(req);
        response[RESPONSE_BODY] = NJson::TJsonValue::object();
        response[RESPONSE_BODY][RESPONSE_FIELD_RECORDS] = NJson::ToVectorJson(
            collection.Find(NJson::TJsonValue::object(), pagination.skip, pagination.limit, NJson::TJsonValue::object()));
        response[RESPONSE_BODY][RESPONSE_FIELD_RECORDS_COUNT] = collection.Count();
    }

    template <class TCollection>
    void RestGetByIdHandler(TCollection& collection, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& recordId = req.matches[1];
        const auto& record = collection.FindById(recordId);
        if (record.has_value()) {
            response[RESPONSE_BODY] = record->ToJson();
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }

    template <class TCollection, class TValidator>
    void RestPostHandler(TCollection& collection, const httplib::Request& req, NJson::TJsonValue& response) {
        const NJson::TJsonValue& jsonRecord = NJson::TJsonValue::parse(req.body);
        TValidator validator(jsonRecord);
        if (validator.Validate(collection)) {
            const auto& newRecord = collection.CreateAndReturn(collection.ToRecord(jsonRecord));
            if (newRecord.has_value()) {
                response[RESPONSE_BODY] = {{ RECORD_FIELD_ID, newRecord->GetId() }};
            } else {
                response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
                response[RESPONSE_ERROR] = RESPONSE_ERROR_INSERT;
            }
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
            response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        }
    }

    template <class TCollection, class TRecord, class TValidator>
    void RestPutHandler(TDataSource& dataSource, TCollection& collection, const httplib::Request& req, NJson::TJsonValue& response) {
        const NJson::TJsonValue& jsonRecord = NJson::TJsonValue::parse(req.body);
        TValidator validator(jsonRecord);
        if (validator.Validate(collection)) {
            const TString& recordId = NJson::GetString(jsonRecord, RECORD_FIELD_ID, "");
            collection.FindByIdAndModify(recordId, TRecord(jsonRecord));
            response[RESPONSE_BODY] = {{ RECORD_FIELD_ID, recordId }};
        } else {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_VALIDATION_ERROR;
            response[RESPONSE_VALIDATION_ERRORS] = validator.GetValidationErrors();
        }
    }

    template <class TCollection>
    void RestDeleteHandler(TDataSource& dataSource, TCollection& collection, const httplib::Request& req, NJson::TJsonValue& response) {
        const TString& recordId = req.matches[1];
        const bool isSuccess = collection.RemoveById(recordId);
        if (!isSuccess) {
            response[RESPONSE_STATUS] = RESPONSE_STATUS_ERROR;
            response[RESPONSE_ERROR] = RESPONSE_ERROR_NOT_FOUND;
        }
    }
}
