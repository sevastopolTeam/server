#include "user_collection.h"

#include <iostream>

namespace NEnglish {

	bool TCollectionUser::Register(const TRecordUser& user) {
	    return Master->Insert(DbName, CollectionName, user.ToJson());
	}

	bool TCollectionUser::IsAlreadyRegistred(const TRecordUser& user)
	{
	    return Master->Find(DbName, CollectionName, user.GetUniqSelector()).size();
	}

}