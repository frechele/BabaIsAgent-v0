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
    // BABA
    // Change target's type to BABA
    // ----------------------------------------------------------------------
    auto BabaEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)rule;

        target.SetType(ObjectType::BABA);
        target.SetEffectType(EffectType::BABA);
    };
    effects.emplace(EffectType::BABA, BabaEffect);
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
    effects.emplace(EffectType::YOU, YouEffect);

    // ----------------------------------------------------------------------
    // WIN
    // If a YOU object contacts this object, the level is won.
    // ----------------------------------------------------------------------
    auto WinEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects.emplace(EffectType::WIN, WinEffect);

    // ----------------------------------------------------------------------
    // STOP
    // If a YOU object contacts this object, the level is won.
    // ----------------------------------------------------------------------
    auto StopEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects.emplace(EffectType::STOP, StopEffect);

    // ----------------------------------------------------------------------
    // MELT
    // Enchant target with MELT.
    // ----------------------------------------------------------------------
    auto MeltEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects.emplace(EffectType::MELT, MeltEffect);

    // ----------------------------------------------------------------------
    // HOT
    // Destroy any MELT object that is or intersects with it
    // ----------------------------------------------------------------------
    auto HotEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)rule;
        
        auto objects = game.FindObjectsByPosition(target);

        for (auto& object : objects)
        {
            if (object->GetEffects().test(
                    static_cast<std::size_t>(EffectType::MELT)))
            {
                game.DestroyObject(*object);
            }
        }
    };
    effects.emplace(EffectType::HOT, HotEffect);
}

Effects::Effects()
{
    ImplementBlockEffects();
    ImplementNonBlockEffects();
}
}  // namespace Baba
