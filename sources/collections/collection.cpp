#include "collection.h"

// template <class TRecord>
// bool ICollection<TRecord>::Create(const TRecord& record) {
//     return Master->Insert(DbName, CollectionName, record);
// }

template <class TRecord>
int ICollection<TRecord>::Test() {
    return 5;
}

// template <class TRecord>
// bool ICollection<TRecord>::Save(const TRecord& record) {
//     if (record.IsNewRecord()) {
//         Master->Insert(DbName, CollectionName, record);
//     } else {
//         // TODO
//     }
// }

// template <class TRecord>
// TRecord ICollection::FindById(const TString& recordId) {
//     return 
// }
