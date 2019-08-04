// Copyright(c) 2019 Junyeong Park

#ifndef BABA_ENTITY_TYPE_H
#define BABA_ENTITY_TYPE_H

namespace Baba
{
//!
//! \brief Enumerator of entity types
//!
enum class EntityType
{
#define TEXT(a) TEXT_##a,
#define BLOCK(a) BLOCK_##a, TEXT_##a,
#include "EntityType.def"
#undef TEXT
#undef BLOCK

    INVALID,
};
}  // namespace Baba

#endif  // BABA_ENTITY_TYPE_H
