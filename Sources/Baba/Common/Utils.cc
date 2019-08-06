// Copyright(c) 2019 Hyeonsu Kim

#include <Baba/Common/Utils.h>

namespace Baba::Utils
{
ObjectType EffectToObject(EffectType effectType)
{
    std::string_view str(EFFECT_TYPE_STR[static_cast<std::size_t>(effectType)]);

    for (int i = 0; i < static_cast<int>(ObjectType::COUNT); ++i)
    {
        if (OBJECT_TYPE_STR[i] == str)
        {
            return ObjectType(i);
        }
    }

    return ObjectType::INVALID;
}
}  // namespace Baba
