// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Game/Game.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

namespace Baba
{
Game::Game(std::size_t width, std::size_t height)
    : width_(width), height_(height), map_(width * height)
{
    // Do nothing
}

std::size_t Game::GetWidth() const
{
    return width_;
}

std::size_t Game::GetHeight() const
{
    return height_;
}

const Object::Arr& Game::At(std::size_t x, std::size_t y) const
{
    return map_[x + y * width_];
}

void Game::Put(std::size_t x, std::size_t y, Object& object)
{
    map_[x + y * width_].emplace_back(&object);
}

void Game::DestroyObject(Object& object)
{
    for (auto& objs : map_)
    {
        for (auto obj = objs.begin(); obj != objs.end(); ++obj)
        {
            if (*obj == &object)
            {
                objs.erase(obj);
                return;
            }
        }
    }
}

Object::Arr Game::FindObjectsByType(ObjectType type) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (Object* obj : objs)
        {
            if (obj->type_ == type)
            {
                result.emplace_back(obj);
            }
        }
    }

    return result;
}

Object::Arr Game::FindObjectsByProperty(EffectType property) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (Object* obj : objs)
        {
            if (obj->GetEffects().test(static_cast<std::size_t>(property)))
            {
                result.emplace_back(obj);
            }
        }
    }

    return result;
}

Object::Arr Game::FindObjectsByPosition(const Object& object) const
{
    for (auto& objs : map_)
    {
        for (Object* obj : objs)
        {
            if (obj == &object)
            {
                return objs;
            }
        }
    }

    return Object::Arr();
}

void Game::ApplyRules()
{
    auto& rules = gameRules.rules_;
    auto& effects = Effects::GetInstance().effects_;

    for (auto& rule : rules)
    {
        if (rule.verb_ == "IS")
        {
            auto func = effects.at(rule.effect_);
            auto targets = FindObjectsByType(rule.target_);

            for (auto& target : targets)
            {
                func(*this, *target, rule);
            }  
        }
        else if (rule.verb_ == "HAS")
        {
            // Not implemented yet
        }
        else if (rule.verb_ == "MAKE")
        {
            // Not implemented yet
        }
        else
        {
            // throw 
        }
    }
}
}  // namespace Baba
