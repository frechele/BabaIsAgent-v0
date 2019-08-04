// Copyright(c) 2019 Junyeong Park

#include <Baba/Entities/Entity.h>

namespace Baba
{
Entity::Entity()
    : type_(EntityType::INVALID)
{
    // Do nothing
}

Entity::Entity(EntityType type)
    : type_(type)
{
    // Do nothing
}

EntityType Entity::GetType() const
{
    return EntityType::TEXT_EMPTY;
}
}  // namespace Baba
