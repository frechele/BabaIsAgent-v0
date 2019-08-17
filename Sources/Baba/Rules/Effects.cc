// Copyright(c) 2019 Hyeonsu Kim

#include <Baba/Enums/ObjectType.h>
#include <Baba/Rules/Effects.h>

namespace Baba
{
Effects& Effects::GetInstance()
{
    static Effects instance;
    return instance;
}

std::uint8_t Effects::GetPriority(PropertyType propertyType) const
{
    return priorities_.at(propertyType);
}

void Effects::emplace(PropertyType propertyType, EffectFunc func, std::uint8_t priority)
{
    effects_.emplace(propertyType, func);
    priorities_.emplace(propertyType, priority);
}

void Effects::ImplementBlockEffects()
{
    // ----------------------------------------------------------------------
    // DECLARE
    // Change target's type
    // ----------------------------------------------------------------------
    /*auto DeclareEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)rule;

        target.SetType(rule.GetEffect());
    };
    effects_.emplace(PropertyType::DECLARE, DeclareEffect);*/
}

void Effects::ImplementNonBlockEffects()
{
    // ----------------------------------------------------------------------
    // YOU
    // The player can control this object
    // ----------------------------------------------------------------------
    auto YouEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)target;
        (void)rule;
        game.SetGameResult(GameResult::INVALID);
    };
    emplace(PropertyType::YOU, YouEffect, 1);

    // ----------------------------------------------------------------------
    // WIN
    // If a YOU object contacts this object, the level is won.
    // ----------------------------------------------------------------------
    auto WinEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)rule;
    
        auto objs = game.FindObjectsByPosition(target);
        for (auto& obj : objs)
        {
            if (obj->HasProperty(PropertyType::YOU))
            {
                game.SetGameResult(GameResult::WIN);
            }
        }
    };
    emplace(PropertyType::WIN, WinEffect, 2);

    // ----------------------------------------------------------------------
    // MELT
    // Enchant target with MELT.
    // ----------------------------------------------------------------------
    auto MeltEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    emplace(PropertyType::MELT, MeltEffect, 100);

    // ----------------------------------------------------------------------
    // HOT
    // Destroy any MELT object that is or intersects with it
    // ----------------------------------------------------------------------
    auto HotEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)rule;

        auto objects = game.FindObjectsByPosition(target);

        for (auto& object : objects)
        {
            if (!object->IsText() && object->HasProperty(PropertyType::MELT))
            {
                game.DestroyObject(*object);
            }
        }
    };
    emplace(PropertyType::HOT, HotEffect, 101);
}

Effects::Effects()
{
    ImplementBlockEffects();
    ImplementNonBlockEffects();
}

const std::map<PropertyType, Effects::EffectFunc>& Effects::GetEffects() const
{
    return effects_;
}
}  // namespace Baba
