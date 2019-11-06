#pragma once

#include <exception>
#include <functional>

#include "contrib/json/json.h"
#include "contrib/mongo-c-driver/src/libbson/src/bson/bson.h"
#include "contrib/mongo-c-driver/src/libmongoc/src/mongoc/mongoc.h"
#include "util/generic/noncopyable.h"
#include "util/generic/string.h"
#include "util/generic/vector.h"

namespace NMongo {
    class TMongoException : public std::exception {
    private:
        TString Message;

    public:
        TMongoException(bson_error_t error) {
            Message = NString::ToString(static_cast<int>(error.code)) + TString(error.message);
        }

        const char* what() const noexcept override {
            return Message.c_str();
        }
    };

    struct TError {
        TError() {
        }

        TError(bson_error_t error)
            : Message(error.message)
            , Code(error.code)
        {
        }

        TString Message;
        int Code;
    };

    inline void Init() {
        mongoc_init();
    }

    inline void Cleanup() {
        mongoc_cleanup();
    }

    inline void DefaultLogHandler(mongoc_log_level_t level, const char* domain, const char* message, void* userdata) {
        mongoc_log_default_handler(level, domain, message, userdata);
    }

    inline void NoopLogHandler(mongoc_log_level_t level, const char* domain, const char* message, void* userdata) {
        (void)(level);
        (void)(domain);
        (void)(message);
        (void)(userdata);
    }

    inline void SetLogHandler(mongoc_log_func_t handler = &DefaultLogHandler, void* userdata = nullptr) {
        mongoc_log_set_handler(handler, userdata);
    }

    class TBsonValue {
    public:
        TBsonValue();
        TBsonValue(bson_t* value, bool shouldCopy = false);
        TBsonValue(const bson_t* value);
        TBsonValue(const NJson::TJsonValue& json);
        TBsonValue(const TBsonValue& other);
        explicit TBsonValue(const TString& json); // an optimization; consider using NJson::TJsonValue as a safer alternative

        ~TBsonValue();

        TBsonValue& operator=(const TBsonValue& other);

        void Destroy();
        bson_t* Release();

        NJson::TJsonValue ToJson() const;

        operator bson_t*() {
            return Value;
        }
        operator bson_t*() const {
            return Value;
        }

    private:
        bson_t* Value;
    };

    template <typename T>
    class TMongoStructureHolder: public TNonCopyable {
    public:
        inline TMongoStructureHolder(T* value)
            : Value(value)
        {
        }

        virtual ~TMongoStructureHolder() noexcept(false) {
        }

        inline operator T*() {
            return Value;
        }
        inline operator T*() const {
            return Value;
        }

    private:
        T* Value;
    };

    class TReadPreferences: public TNonCopyable {
    public:
        TReadPreferences();
        TReadPreferences(mongoc_read_mode_t mode);
        TReadPreferences(TReadPreferences&& other) noexcept;
        void SetMode(mongoc_read_mode_t mode);
        void SetTags(const TBsonValue& tags);
        bool Validate() const;
        ~TReadPreferences();

        operator mongoc_read_prefs_t*() {
            return Value;
        }
        operator mongoc_read_prefs_t*() const {
            return Value;
        }

    private:
        void EnsureCreated(mongoc_read_mode_t mode);

        mongoc_read_prefs_t* Value = nullptr;
    };

    class TUri : public TMongoStructureHolder<mongoc_uri_t> {
    public:
        TUri(const TString& connectionString);
        ~TUri() override;
    };

    class TClientPool : public TMongoStructureHolder<mongoc_client_pool_t> {
    public:
        TClientPool(const TUri& uri);
        ~TClientPool() override;
    };

    class TClient : public TMongoStructureHolder<mongoc_client_t> {
    public:
        TClient(const TClientPool& pool);
        TClient(TClient&& other);
        ~TClient() override;

    private:
        const TClientPool& Pool;
    };

    class TCollection : public TMongoStructureHolder<mongoc_collection_t> {
        public:
            TCollection(const TClient& client, const TString& db, const TString& collection);
            ~TCollection() override;
    };

    class TCursor : public TMongoStructureHolder<mongoc_cursor_t> {
    public:
        TCursor(mongoc_cursor_t* value);
        ~TCursor() noexcept(false) override;

        std::pair<TBsonValue, bool> Begin();
        std::pair<TBsonValue, bool> Next();
    };

    class TBulkOperation : public TMongoStructureHolder<mongoc_bulk_operation_t> {
    public:
        TBulkOperation(mongoc_bulk_operation_t* value);
        ~TBulkOperation() noexcept(false) override;
    };

    class THelper {
    public:
        THelper(const TString& connectionString);

        bool Insert(const TString& db, const TString& collection,
            const TBsonValue& value, TError* error = nullptr);
        bool Update(const TString& db, const TString& collection,
            const TBsonValue& selector, const TBsonValue& updater, TError* error = nullptr);
        bool Upsert(const TString& db, const TString& collection,
            const TBsonValue& selector, const TBsonValue& updater, TError* error = nullptr);
        bool MultiUpdate(const TString& db, const TString& collection,
            const TBsonValue& selector, const TBsonValue& updater, TError* error = nullptr);
        bool MultiUpsert(const TString& db, const TString& collectionName,
            const TBsonValue& selector, const TBsonValue& updater, TError* error = nullptr);

        bool BulkInsert(const TString& db, const TString& collectionName,
            const TVector<TBsonValue>& values, bool ordered, TError* error = nullptr);

        struct TUpdateParams {
            TBsonValue Selector;
            TBsonValue Updater;
            bool Upsert;
        };
        bool BulkUpdate(const TString& db, const TString& collection,
            const TVector<TUpdateParams>& ops, bool ordered, TError* error = nullptr);

        bool Remove(const TString& db, const TString& collection,
            const TBsonValue& selector, TError* error = nullptr);

        void Find(const TString& db, const TString& collection,
            const std::function<void(const std::pair<TBsonValue, bool>&)>& callback,
            const TBsonValue& selector = TBsonValue(),
            size_t skip = 0, size_t limit = 0,
            const TBsonValue& fields = TBsonValue(),
            const TReadPreferences& readPrefs = TReadPreferences());
        TVector<TBsonValue> Find(const TString& db, const TString& collection,
            const TBsonValue& selector = TBsonValue(),
            size_t skip = 0, size_t limit = 0,
            const TBsonValue& fields = TBsonValue(),
            const TReadPreferences& readPrefs = TReadPreferences());
        TBsonValue FindAndModify(const TString& db, const TString& collection,
            const TBsonValue& query, const TBsonValue& update,
            const TBsonValue& sort = TBsonValue(), bool upsert = false,
            bool retnew = false, bool remove = false,
            const TBsonValue& fields = TBsonValue(), TError* error = nullptr);
        long long Count(const TString& db, const TString& collection,
            const TBsonValue& selector = TBsonValue(),
            size_t skip = 0, size_t limit = 0, TError* error = nullptr);
        void Aggregate(const TString& db, const TString& collection,
            const std::function<void(const std::pair<TBsonValue, bool>&)>& callback,
            const TBsonValue& pipeline,
            const mongoc_query_flags_t flags = MONGOC_QUERY_NONE);
        TVector<TBsonValue> Aggregate(const TString& db, const TString& collection,
            const TBsonValue& pipeline,
            const mongoc_query_flags_t flags = MONGOC_QUERY_NONE);

        // return true then the connection is established
        bool CheckConnection(const TString& db, TError* error = nullptr);

    private:
        TClientPool ClientPool;
    };

}