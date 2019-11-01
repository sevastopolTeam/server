#pragma once

#include <string>

#include "contrib/httplib/httplib.h"
#include "contrib/mongo-c-driver/src/libmongoc/src/mongoc/mongoc.h"

void NumbersHandler(mongoc_collection_t* collection, const httplib::Request& req, httplib::Response& res) {
	auto numbers = req.matches[1];
	res.set_content(numbers, "text/plain");
	bson_t* doc = bson_new();
	bson_oid_t oid;
	bson_oid_init(&oid, NULL);
	BSON_APPEND_OID(doc, "_id", &oid);
	BSON_APPEND_UTF8(doc, "hello", std::string(numbers).c_str());

	bson_error_t error;
	if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
		printf("%s\n", error.message);
	}

	bson_destroy(doc);
}
