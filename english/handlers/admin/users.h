#pragma once

#include "english/handlers/routing.h"

#include "contrib/httplib/httplib.h"
#include "contrib/json/json.h"

#include "english/collections/user_collection.h"

#include "sources/data_source/data_source.h"

#include "util/generic/ctype.h"
#include "util/generic/iostream.h"

namespace NEnglish {

	void GetAdminUsersHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
        NJson::TJsonValue response = {{ RESPONSE_STATUS, RESPONSE_STATUS_OK }};
        
        try {
            if (IsAdmin(dataSource, req)) {

                const int limit = NType::ToInt(req.GetParamValue("PageSize", "0"));
                const int skip = NType::ToInt(req.GetParamValue("Page", "0")) * limit;

                response["Body"] = NJson::TJsonValue::object();
                response["Body"]["Users"] = NJson::ToVectorJson(
                    dataSource.English.CollectionUser.Find(NJson::TJsonValue::object(), skip, limit)
                );
            /*    response[RESPONSE_BODY] = {
                    {
                        RESPONSE_FIELD_TRANSLATIONS,
                        NJson::ToVectorJson(
                            dataSource.English.CollectionTranslation.Find(NJson::TJsonValue::object(), skip, limit)
                        )
                    },
                    {
                        RESPONSE_FIELD_TRANSLATIONS_COUNT,
                        dataSource.English.CollectionTranslation.Count()
                    }
                };*/
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