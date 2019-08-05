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

void Effects::EmplaceEffect(EffectType effectType, std::function<void(Game&, Object&, Rule&)> func)
{
    auto decorated = [effectType, func]([[maybe_unused]]Game& game, [[maybe_unused]]Object& target, [[maybe_unused]]Rule& rule) {
        EffectsBitset bitset;
        bitset.set(static_cast<std::size_t>(effectType));
        target.enchants_.emplace(rule.ruleID_, bitset);

        func(game, target, rule);
    };

    effects_.emplace(effectType, decorated);
}

void Effects::ImplementBlockEffects()
{
    // ----------------------------------------------------------------------
    // BABA
    // Change target's type to BABA
    // ----------------------------------------------------------------------
    auto BabaEffect = []([[maybe_unused]]Game& game, [[maybe_unused]]Object& target, [[maybe_unused]]Rule& rule) {
        target.type_ = ObjectType::BABA;
        target.effectType_ = EffectType::BABA;
    };
    EmplaceEffect(EffectType::BABA, BabaEffect);
}

void Effects::ImplementNonBlockEffects()
{
    // ----------------------------------------------------------------------
    // MELT
    // Enchant target with MELT.
    // ----------------------------------------------------------------------
    auto MeltEffect = []([[maybe_unused]]Game& game, [[maybe_unused]]Object& target, [[maybe_unused]]Rule& rule) {
        // Do nothing
    };
    EmplaceEffect(EffectType::MELT, MeltEffect);

    // ----------------------------------------------------------------------
    // HOT
    // Destroy any MELT object that is or intersects with it
    // ----------------------------------------------------------------------
    auto HotEffect = []([[maybe_unused]]Game& game, [[maybe_unused]]Object& target, [[maybe_unused]]Rule& rule) {
        auto objects = game.FindObjectsByPosition(target);

        for (auto& object : objects)
        {
            if (object->GetEffects().test(static_cast<std::size_t>(EffectType::MELT)))
            {
                game.DestroyObject(*object);
            }
        }
    };
    EmplaceEffect(EffectType::HOT, HotEffect);
}

Effects::Effects()
{
    ImplementBlockEffects();
    ImplementNonBlockEffects();
}
} // namespace Baba
