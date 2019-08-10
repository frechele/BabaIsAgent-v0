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

void Effects::ImplementBlockEffects()
{
    // ----------------------------------------------------------------------
    // DECLARE
    // Change target's type
    // ----------------------------------------------------------------------
    auto DeclareEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)rule;

        target.SetType(rule.GetEffect());
    };
    effects_.emplace(PropertyType::DECLARE, DeclareEffect);
}

void Effects::ImplementNonBlockEffects()
{
    // ----------------------------------------------------------------------
    // YOU
    // The player can control this object
    // ----------------------------------------------------------------------
    auto YouEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects_.emplace(PropertyType::YOU, YouEffect);

    // ----------------------------------------------------------------------
    // WIN
    // If a YOU object contacts this object, the level is won.
    // ----------------------------------------------------------------------
    auto WinEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects_.emplace(PropertyType::WIN, WinEffect);

    // ----------------------------------------------------------------------
    // MELT
    // Enchant target with MELT.
    // ----------------------------------------------------------------------
    auto MeltEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects_.emplace(PropertyType::MELT, MeltEffect);

    // ----------------------------------------------------------------------
    // HOT
    // Destroy any MELT object that is or intersects with it
    // ----------------------------------------------------------------------
    auto HotEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)rule;

        auto objects = game.FindObjectsByPosition(target);

        for (auto& object : objects)
        {
            if (object->HasProperty(PropertyType::MELT))
            {
                game.DestroyObject(*object);
            }
        }
    };
    effects_.emplace(PropertyType::HOT, HotEffect);
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
