// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_TYPE_H
#define BABA_OBJECT_TYPE_H

#include <string>
#include <vector>

namespace Baba
{
//!
//! \brief Enumerator of entity types
//!
enum class ObjectType
{
    INVALID,
#define TEXT(a) TEXT_##a,
#define VERB(a) TEXT_##a,
#define PROPERTY(a) TEXT_##a,
#define BLOCK(a) a, TEXT_##a,
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef PROPERTY
#undef BLOCK
    COUNT,
};

enum class VerbType
{
    INVALID,
    IS,
    HAS,
    MAKE
};

enum class EffectType
{
    INVALID,
#define TEXT(a)
#define VERB(a) a,
#define BLOCK(a) a,
#define PROPERTY(a) a,
#include "ObjectType.def"
#undef TEXT
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
};

const std::vector<std::string> OBJECT_TYPE_STR {
    "INVALID",
#define TEXT(a) "TEXT_"#a,
#define VERB(a) "TEXT_"#a,
#define PROPERTY(a) "TEXT_"#a,
#define BLOCK(a) #a, "TEXT_"#a,
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef PROPERTY
#undef BLOCK
};

const std::vector<std::string> EFFECT_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a)#a,
#define PROPERTY(a)#a,
#define BLOCK(a)#a,
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef PROPERTY
#undef BLOCK
};

const std::vector<std::string> NOUN_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a)
#define PROPERTY(a)
#define BLOCK(a)#a,
#include "ObjectType.def"
#undef TEXT
#undef VERB
#undef PROPERTY
#undef BLOCK
};

const std::vector<std::string> VERB_TYPE_STR {
    "INVALID",
    "IS",
    "HAS",
    "MAKE",
};

const std::vector<std::string> PROPERTY_TYPE_STR {
    "INVALID",
#define TEXT(a)
#define VERB(a)
#define PROPERTY(a)#a,
#define BLOCK(a)
#include "ObjectType.def"
#undef TEXT

#undef PROPERTY
#undef BLOCK
};
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
