#pragma once

#include "collection.h"
#include "library/mongo/wrappers.h"

class TCollectionUser : public ICollection {
public:
    using ICollection::ICollection;

    bool Register(const NJson::TJsonValue& user);
};
