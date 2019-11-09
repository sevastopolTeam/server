#pragma once

#include <iostream>

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

void HiHandler(TDataSource& dataSource, const httplib::Request& req, httplib::Response& res) {
    TVector<NMongo::TBsonValue> result = dataSource.Base.Find();

    TString ans;
    for (const auto& i : result) {
        if (!ans.empty()) {
            ans += ",";
        }
        ans += i.ToJson().dump();
    }
    ans = "[" + ans + "]";
    std::cout << ans << std::endl;

    res.set_content(ans, "text/plain");
}

