#include "hi.h"

#include <stdio.h>
#include <string>

void HiHandler(mongoc_collection_t* Collection, const httplib::Request& req, httplib::Response& res) {
    const bson_t* doc;
    bson_t* query = bson_new();
    mongoc_cursor_t* cursor = mongoc_collection_find_with_opts(Collection, query, NULL, NULL);

    std::string ans;
    while (mongoc_cursor_next(cursor, &doc)) {
        char* str = bson_as_canonical_extended_json(doc, NULL);
        printf("%s\n", str);
        if (!ans.empty()) {
            ans += ",";
        }
        ans += std::string(str);
        bson_free(str);
    }

    bson_destroy(query);
    mongoc_cursor_destroy(cursor);
    ans = "[" + ans + "]";
    res.set_content(ans, "text/plain");
}

