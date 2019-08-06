// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Objects/Object.h>

namespace Baba
{
Object::Object()
{
    // Do nothing
}

const EffectsBitset Object::GetEffects() const
{
    EffectsBitset result;

    for (const auto& enchant : enchants)
    {
        result |= enchant.second;
    }

    return result;
}

bool Object::operator==(const Object& other) const
{
    return (this == &other);
}

bool Object::operator!=(const Object& other) const
{
    return !(*this == other);
}
}  // namespace Baba
