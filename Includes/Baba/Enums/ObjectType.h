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
#define BLOCK(a) a, TEXT_##a,
#include "ObjectType.def"
#undef TEXT
#undef BLOCK
};

const std::string OBJECT_TYPE_STR[] {
    "INVALID",
#define TEXT(a) "TEXT_"#a,
#define BLOCK(a) #a, "TEXT_"#a,
#include "ObjectType.def"
#undef TEXT
#undef BLOCK
};
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
