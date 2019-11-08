include_directories(
	../../../contrib/mongo-c-driver/libbson
	../../../contrib/mongo-c-driver/libmongoc
	../../../contrib/mongo-c-driver/libbson/src
	../../../contrib/mongo-c-driver/libmongoc/src
)

add_executable(mongoc-stat ../../../contrib/mongo-c-driver/tools/mongoc-stat.c)

target_link_libraries (mongoc-stat mongoc_static)
