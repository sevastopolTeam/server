#pragma once

#include "httplib.h"
#include "mongoc/mongoc.h"

void NumbersHandler(mongoc_collection_t* Collection, const httplib::Request& req, httplib::Response& res);