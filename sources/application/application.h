#pragma once

#include "contrib/httplib/httplib.h"
#include "library/mongo/wrappers.h"
#include "sources/data_source/data_source.h"

class TApplication {
public:
    TApplication();

    ~TApplication();
private:
    httplib::Server Server;
    std::unique_ptr<TDataSource> DataSource;
 };

