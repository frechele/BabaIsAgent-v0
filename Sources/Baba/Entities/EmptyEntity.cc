// Copyright(c) 2019 Junyeong Park

#include <Baba/Entities/EmptyEntity.h>

namespace Baba
{
EntityType EmptyBlock::GetType() const
{
    return EntityType::BLOCK_EMPTY;
}

EntityType EmptyText::GetType() const
{
    return EntityType::TEXT_EMPTY;
}
}  // namespace Baba
