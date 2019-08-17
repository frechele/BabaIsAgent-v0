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
    auto YouEffect = [](Game& game, Object& target) {
        Direction dir;

        switch (game.GetNowAction())
        {
            case Action::UP:
                dir = Direction::UP;
                break;
            case Action::DOWN:
                dir = Direction::DOWN;
                break;
            case Action::LEFT:
                dir = Direction::LEFT;
                break;
            case Action::RIGHT:
                dir = Direction::RIGHT;
                break;
            default:
                return;
        }

        auto objs = game.TieStuckMoveableObjects(target, dir);
        game.MoveObjects(objs, dir);
    };
    emplace(PropertyType::YOU, YouEffect, 100);

    // ----------------------------------------------------------------------
    // WIN
    // If a YOU object contacts this object, the level is won.
    // ----------------------------------------------------------------------
    auto WinEffect = [](Game& game, Object& target) {
        auto objs = game.FindObjectsByPosition(target);
        for (auto& obj : objs)
        {
            if (obj->HasProperty(PropertyType::YOU))
            {
                game.SetGameResult(GameResult::WIN);
            }
        }
    };
    emplace(PropertyType::WIN, WinEffect, 101);

    auto WordEffect = [](Game& game, Object& target) {
        (void)game;
        (void)target;
    };
    emplace(PropertyType::WORD, WordEffect, 0);

    // ----------------------------------------------------------------------
    // PUSH
    // Make target pushable and make it solid.
    // ----------------------------------------------------------------------
    auto PushEffect = [](Game& game, Object& target) {
        (void)game;
        (void)target;
    };
    emplace(PropertyType::PUSH, PushEffect, 10);

    // ----------------------------------------------------------------------
    // STOP
    // Make target solid.
    // ----------------------------------------------------------------------
    auto StopEffect = [](Game& game, Object& target) {
        (void)game;
        (void)target;
    };
    emplace(PropertyType::STOP, StopEffect, 11);

    // ----------------------------------------------------------------------
    // MELT
    // Enchant target with MELT.
    // ----------------------------------------------------------------------
    auto MeltEffect = [](Game& game, Object& target) {
        (void)game;
        (void)target;
    };
    emplace(PropertyType::MELT, MeltEffect, 12);

    // ----------------------------------------------------------------------
    // HOT
    // Destroy any MELT object that is or intersects with it
    // ----------------------------------------------------------------------
    auto HotEffect = [](Game& game, Object& target) {
        auto objects = game.FindObjectsByPosition(target);

        for (auto& object : objects)
        {
            if (!object->IsText() && object->HasProperty(PropertyType::MELT))
            {
                game.DestroyObject(*object);
            }
        }
    };
    emplace(PropertyType::HOT, HotEffect, 50);
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
