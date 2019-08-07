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

Game::~Game()
{
    for (auto& obj : objects_)
    {
        delete obj;
    }
    objects_.clear();
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

Object& Game::Put(std::size_t x, std::size_t y)
{
    objects_.emplace_back(new Object);
    map_[x + y * width_].emplace_back(objects_.back());

    return *map_[x + y * width_].back();
}

void Game::DestroyObject(Object& object)
{
    for (auto& objs : map_)
    {
        for (auto obj = objs.begin(); obj != objs.end(); ++obj)
        {
            if (**obj == object)
            {
                (*obj)->Destroy();
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
        for (auto& obj : objs)
        {
            if (obj->GetType() == type)
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
        for (auto& obj : objs)
        {
            if (obj->GetEffects().test(static_cast<std::size_t>(property)))
            {
                result.emplace_back(obj);
            }
        }
    }

    return result;
}

Object::Arr Game::FindObjectsByPosition(const Object& target) const
{
    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (*obj == target)
            {
                return objs;
            }
        }
    }

    return Object::Arr();
}

void Game::ApplyRules()
{
    auto& rules = gameRules.GetAllRules();
    auto& effects = Effects::GetInstance().effects;

    for (auto& rule : rules)
    {
        if (rule.GetVerb() == VerbType::IS)
        {
            auto targets = FindObjectsByType(rule.GetTarget());

            for (auto& target : targets)
            {
                target->SetEffect(rule.GetEffect(), rule.GetRuleID());
            }
        }
    }

    for (auto& rule : rules)
    {
        if (rule.GetVerb() == VerbType::IS)
        {
            auto func = effects.at(rule.GetEffect());
            auto targets = FindObjectsByType(rule.GetTarget());

            for (auto& target : targets)
            {
                func(*this, *target, rule);
            }
        }
        else if (rule.GetVerb() == VerbType::HAS)
        {
            // Not implemented yet
        }
        else if (rule.GetVerb() == VerbType::MAKE)
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
