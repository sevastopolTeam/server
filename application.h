#pragma once

#include "data_source.h"
#include "contrib/httplib/httplib.h"
#include "library/mongo/wrappers.h"

class TApplication {
public:
    TApplication();

    ~TApplication();
private:
    httplib::Server Server;
    std::unique_ptr<TDataSource> DataSource;
 };

