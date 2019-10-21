#pragma once

#include "httplib.h"
#include "mongoc/mongoc.h"

class TApplication {
public:
    TApplication();

    ~TApplication();
private:
    void HiHandler(const httplib::Request& req, httplib::Response& res);
    void NumbersHandler(const httplib::Request& req, httplib::Response& res);

    httplib::Server Server;
    mongoc_client_t* Client;
    mongoc_collection_t* Collection;
};

