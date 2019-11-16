#include "user_collection.h"

#include <iostream>

bool TCollectionEnglishUser::Register(const TRecordEnglishUser& user) {
    return Master->Insert(DbName, CollectionName, user.ToJson());
}

bool TCollectionEnglishUser::IsAlreadyRegistred(const TRecordEnglishUser& user)
{
    return Master->Find(DbName, CollectionName, user.GetUniqSelector()).size();
}
