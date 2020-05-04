#pragma once

#include "contrib/httplib/httplib.h"
#include "sources/data_source/data_source.h"

class TApplication {
public:
    TApplication(NJson::TJsonValue& config);

    void Start();

    ~TApplication();
private:
    THolder<TDataSource> DataSource;
    THolder<httplib::Server> Server;

    void AddEnglishHandlers();

    NJson::TJsonValue& Config;
 };
