#include "application.h"

#include <iostream>

#include <handlers/hi.h>
#include <handlers/numbers.h>

TApplication::TApplication() {
    std::cout << "Starting server..." << std::endl;
    mongoc_init();
    Client = mongoc_client_new("mongodb://localhost:1235");
    Collection = mongoc_client_get_collection(Client, "prod", "base");

    Server.Get("/hi",               [&](const httplib::Request& req, httplib::Response& res){ HiHandler(Collection, req, res);});
    Server.Get(R"(/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res){ NumbersHandler(Collection, req, res);});

    std::cout << "Server started" << std::endl;
    Server.listen("0.0.0.0", 1234);
}

TApplication::~TApplication() {
    Server.stop();
    mongoc_collection_destroy(Collection);
    mongoc_client_destroy(Client);
    mongoc_cleanup();
}

