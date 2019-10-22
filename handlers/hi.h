#pragma once

#include "contrib/httplib/httplib.h"
#include "mongoc/mongoc.h"

void HiHandler(mongoc_collection_t* Collection, const httplib::Request& req, httplib::Response& res);

