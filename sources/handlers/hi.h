#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

#include "util/generic/iostream.h"

void HiHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    TVector<TRecordBase> result = dataSource.CollectionBase.Find();

    TString ans;
    for (const auto& i : result) {
        if (!ans.empty()) {
            ans += ",";
        }
        ans += i.ToJson().dump();
    }
    ans = "[" + ans + "]";
    INFO_LOG << ans << Endl;

    res.set_content(ans, "text/plain");
}

