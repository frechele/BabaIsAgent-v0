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

        target.SetName(ObjectName::BABA);
    };
    effects.emplace(ObjectName::BABA, BabaEffect);
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
    effects.emplace(ObjectName::YOU, YouEffect);

    // ----------------------------------------------------------------------
    // WIN
    // If a YOU object contacts this object, the level is won.
    // ----------------------------------------------------------------------
    auto WinEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects.emplace(ObjectName::WIN, WinEffect);

    // ----------------------------------------------------------------------
    // PUSH
    // This object can be pushed.
    // ----------------------------------------------------------------------
    auto PushEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects.emplace(ObjectName::WIN, PushEffect);

    // ----------------------------------------------------------------------
    // MELT
    // Enchant target with MELT.
    // ----------------------------------------------------------------------
    auto MeltEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)game;
        (void)target;
        (void)rule;
    };
    effects.emplace(ObjectName::MELT, MeltEffect);

    // ----------------------------------------------------------------------
    // HOT
    // Destroy any MELT object that is or intersects with it
    // ----------------------------------------------------------------------
    auto HotEffect = [](Game& game, Object& target, const Rule& rule) {
        (void)rule;
        
        auto objects = game.FindObjectsByPosition(target);

        for (auto& object : objects)
        {
            if (object->GetProperty().test(
                    static_cast<std::size_t>(ObjectName::MELT)))
            {
                game.DestroyObject(*object);
            }
        }
    };
    effects.emplace(ObjectName::HOT, HotEffect);
}

Effects::Effects()
{
    ImplementBlockEffects();
    ImplementNonBlockEffects();
}
}  // namespace Baba
