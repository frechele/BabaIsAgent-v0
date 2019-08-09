// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_TYPE_H
#define BABA_OBJECT_TYPE_H

#include <string>
#include <vector>

namespace Baba
{
enum class ObjectName
{
    INVALID,
#define TEXT(a)
#define UNIQUE(a) a,
#define VERB(a) a,
#define BLOCK(a) a,
#define PROPERTY(a) a,
#include "ObjectType.def"
#undef TEXT
#undef UNIQUE
#undef VERB
#undef PROPERTY
#undef BLOCK
    COUNT,
};

enum class WordClass
{
    INVALID,
    NOUN,
    VERB,
    PROPERTY,
    UNIQUE,
};

const std::vector<std::string> NOUN_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a)
#define UNIQUE(a)
#define PROPERTY(a)
#define BLOCK(a) #a,
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef UNIQUE
#undef PROPERTY
#undef BLOCK
};

const std::vector<std::string> VERB_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a) #a,
#define UNIQUE(a)
#define PROPERTY(a)
#define BLOCK(a)
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef UNIQUE
#undef PROPERTY
#undef BLOCK
};

const std::vector<std::string> PROPERTY_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a)
#define UNIQUE(a)
#define PROPERTY(a) #a,
#define BLOCK(a)
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef UNIQUE
#undef PROPERTY
#undef BLOCK
};

const std::vector<std::string> UNIQUE_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a)
#define UNIQUE(a) #a,
#define PROPERTY(a)
#define BLOCK(a)
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef UNIQUE
#undef PROPERTY
#undef BLOCK
};
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
