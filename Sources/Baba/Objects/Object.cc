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

    for (const auto& enchant : enchants_)
    {
        result |= enchant.second;
    }

    return result;
}
}  // namespace Baba
