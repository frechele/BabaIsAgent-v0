// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_TYPE_H
#define BABA_OBJECT_TYPE_H

#include <string>

namespace Baba
{
//!
//! \brief Enumerator of entity types
//!
enum class ObjectType
{
    INVALID,
#define TEXT(a) TEXT_##a,
#define PROPERTY(a) TEXT_##a,
#define BLOCK(a) a, TEXT_##a,
#include "ObjectType.def"
#undef TEXT
#undef PROPERTY
#undef BLOCK
};

enum class EffectType
{
    INVALID,
    TEXT,
#define TEXT(a)
#define BLOCK(a) a,
#define PROPERTY(a) a,
#include "ObjectType.def"
#undef TEXT
#undef PROPERTY
#undef BLOCK
    COUNT,
};

const std::string OBJECT_TYPE_STR[] {
    "INVALID",
#define TEXT(a) "TEXT_"#a,
#define PROPERTY(a) "TEXT_"#a,
#define BLOCK(a) #a, "TEXT_"#a,
#include "ObjectType.def"
#undef TEXT
#undef PROPERTY
#undef BLOCK
};

const std::string EFFECT_TYPE_STR[] {
    "INVALID",
    "TEXT",
#define TEXT(a)
#define PROPERTY(a) #a,
#define BLOCK(a) #a,
#include "ObjectType.def"
#undef TEXT
#undef PROPERTY
#undef BLOCK
};
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
