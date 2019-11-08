include_directories(
	../../../contrib/mongo-c-driver/libbson/src
	../../../contrib/mongo-c-driver/common
	../../../contrib/mongo-c-driver
)

add_library(bson_static
    ../common/common-b64.c
    ../common/common-md5.c
    ../libbson/src/bson/bcon.c
    ../libbson/src/bson/bson-atomic.c
    ../libbson/src/bson/bson-clock.c
    ../libbson/src/bson/bson-context.c
    ../libbson/src/bson/bson-decimal128.c
    ../libbson/src/bson/bson-error.c
    ../libbson/src/bson/bson-iso8601.c
    ../libbson/src/bson/bson-iter.c
    ../libbson/src/bson/bson-json.c
    ../libbson/src/bson/bson-keys.c
    ../libbson/src/bson/bson-md5.c
    ../libbson/src/bson/bson-memory.c
    ../libbson/src/bson/bson-oid.c
    ../libbson/src/bson/bson-reader.c
    ../libbson/src/bson/bson-string.c
    ../libbson/src/bson/bson-timegm.c
    ../libbson/src/bson/bson-utf8.c
    ../libbson/src/bson/bson-value.c
    ../libbson/src/bson/bson-version-functions.c
    ../libbson/src/bson/bson-writer.c
    ../libbson/src/bson/bson.c
    ../libbson/src/jsonsl/jsonsl.c
)

target_compile_definitions(bson_static
    PUBLIC BSON_STATIC
    PRIVATE BSON_COMPILATION
	JSONSL_PARSE_NAN
)
