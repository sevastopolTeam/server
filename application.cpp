#include "application.h"

#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>

TApplication::TApplication() {
    std::cout << "Starting server..." << std::endl;
    mongoc_init();
    client = mongoc_client_new("mongodb://localhost:1235");
    collection = mongoc_client_get_collection(client, "prod", "base");

    svr.Get("/hi", [&](const httplib::Request& req, httplib::Response& res){ this->HiHandler(req, res);}); 
    svr.Get(R"(/numbers/(\d+))", [&](const httplib::Request& req, httplib::Response& res){ this->NumbersHandler(req, res);});

    std::cout << "Server started" << std::endl;
    svr.listen("0.0.0.0", 1234);
}

void TApplication::HiHandler(const httplib::Request& req, httplib::Response& res) {
    const bson_t* doc;
    bson_t* query = bson_new ();
    mongoc_cursor_t* cursor = mongoc_collection_find_with_opts (collection, query, NULL, NULL);

    std::string ans;
    while (mongoc_cursor_next (cursor, &doc)) {
        char* str = bson_as_canonical_extended_json (doc, NULL);
        printf ("%s\n", str);
        if (!ans.empty()) {
            ans += ",";
        }   
        ans += std::string(str);
        bson_free (str);
    }

    bson_destroy (query);
    mongoc_cursor_destroy (cursor);
    ans = "[" + ans + "]";
    res.set_content(ans, "text/plain");
}

void TApplication::NumbersHandler(const httplib::Request& req, httplib::Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
    bson_t* doc = bson_new ();
    bson_oid_t oid;
    bson_oid_init (&oid, NULL);
    BSON_APPEND_OID (doc, "_id", &oid);
    BSON_APPEND_UTF8 (doc, "hello", std::string(numbers).c_str());

    bson_error_t error;
    if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
        printf ("%s\n", error.message);
    }   

    bson_destroy (doc);
}

TApplication::~TApplication() {
        svr.stop();
        mongoc_collection_destroy(collection);
        mongoc_client_destroy(client);
        mongoc_cleanup();
}

