#include "user.h"

bool TCollectionUser::Register(const NJson::TJsonValue& user) {
    NJson::TJsonValue selector;
    selector["name"] = user["name"];
    if (!Master->Find(DbName, CollectionName, selector).empty()) {
        return false;
    }
    Master->Insert(DbName, CollectionName, user);
    return true;
}
