// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_TYPE_H
#define BABA_OBJECT_TYPE_H

namespace Baba
{
//!
//! \brief Enumerator of entity types
//!
enum class ObjectType
{
#define TEXT(a) TEXT_##a,
#define BLOCK(a) a, TEXT_##a,
#include "ObjectType.def"
#undef TEXT
#undef BLOCK

    INVALID,
};
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
