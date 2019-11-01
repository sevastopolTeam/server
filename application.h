#pragma once

#include "contrib/httplib/httplib.h"
#include "contrib/mongo-c-driver/src/libmongoc/src/mongoc/mongoc.h"

class TApplication {
public:
    TApplication();

    ~TApplication();
private:
    httplib::Server Server;
    mongoc_client_t* Client;
    mongoc_collection_t* Collection;
};

