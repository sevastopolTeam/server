#include "session_collection.h"
#include "contrib/json/json.h"

namespace NEnglish {

    bool TCollectionSession::Create(const TRecordSession& session) {
        return Master->Insert(DbName, CollectionName, session.ToJson());
    }

    TVector<TRecordSession> TCollectionSession::Find() {
        TVector<NMongo::TBsonValue> result = Master->Find(DbName, CollectionName);
        TVector<TRecordSession> records;
        for (const auto& a : result) {
            records.push_back(TRecordSession(a.ToJson()));
        }
        return records;
    }

}
