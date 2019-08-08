// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Common/Utils.h>
#include <Baba/Game/Game.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

#include <algorithm>
#include <stdexcept>

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

Object::Arr Game::FilterObjectByFunction(const Object::Arr& objects,
                                         std::function<bool(Object&)> func) const
{
    Object::Arr result;

    for (auto& obj : objects)
    {
        if (func(*obj))
        {
            result.emplace_back(obj);
        }
    }

    return result;
}

const Game::Pos Game::GetPositionByObject(const Object& target) const
{
    for (std::size_t y = 0; y < GetHeight(); y++)
    {
        for (std::size_t x = 0; x < GetWidth(); x++)
        {
            const auto& objs = map_[x + y * width_];
            
            for (auto& obj : objs)
            {
                if (*obj == target)
                {
                    return {x, y};
                }
            }
        }
    }

    throw std::runtime_error("Invalid target");
}

void Game::ApplyRules()
{
    auto& rules = gameRules.GetAllRules();
    auto& effects = Effects::GetInstance().effects;
    
    for (auto& rule : rules)
    {
        if (rule.GetVerb() == EffectType::IS)
        {
            auto targets = FindObjectsByType(Utils::EffectToObject(rule.GetTarget()));

            for (auto& target : targets)
            {
                target->SetEffect(rule.GetEffect(), rule.GetRuleID());
            }
        }
    }

    for (auto& rule : rules)
    {
        if (rule.GetVerb() == EffectType::IS)
        {
            auto func = effects.at(rule.GetEffect());
            auto targets = FindObjectsByType(Utils::EffectToObject(rule.GetTarget()));

            for (auto& target : targets)
            {
                func(*this, *target, rule);
            }
        }
        else if (rule.GetVerb() == EffectType::HAS)
        {
            // Not implemented yet
        }
        else if (rule.GetVerb() == EffectType::MAKE)
        {
            // Not implemented yet
        }
        else
        {
            // throw
        }
    }
}

bool Game::ValidatePosition(const std::size_t& x, const std::size_t& y) const
{
    return x >= 0 && y >= 0 && x < width_ && y < height_;
}

void Game::ParseRules()
{
    // Find verbs
    std::vector<std::tuple<Object*, Pos>> verbs;

    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (Utils::ValidateWord(*obj, { WordClass::VERB }))
            {
                verbs.emplace_back(obj, GetPositionByObject(*obj));
            }
        }
    }

    static std::tuple<std::size_t, std::size_t> vec[] = {{1, 0}, {0, 1}};

    // Syntax analyzing
    // The syntax currently implemented is:
    // 3 words:
    // - NOUN VERB NOUN
    // - NOUN VERB PROPERTY
    for (auto& verb : verbs)
    {
        // [i == 0]: Read from left to right
        // [i == 1]: Read from up to down
        //for (std::size_t i = 0; i < 2; ++i)
        for (auto [dx, dy] : vec)
        {
            const auto [obj, pos] = verb;
            auto [x, y] = pos;
            
            // Check out of bounds
            if (!(ValidatePosition(x - dx, y - dy) && ValidatePosition(x + dx, y + dy)))
            {
                continue;
            }

            // Check syntax
            Object::Arr subjects = FilterObjectByFunction(At(x - dx, y - dy), 
                [](Object& obj)->bool{
                return Utils::ValidateWord(obj, { WordClass::NOUN });
            });

            Object::Arr complements = FilterObjectByFunction(At(x + dx, y + dy), 
                [](Object& obj)->bool{
                return Utils::ValidateWord(obj, { WordClass::NOUN, WordClass::PROPERTY });
            });

            if (subjects.empty() || complements.empty())
            {
                continue;
            }

            // Make rules
            for (auto& subject : subjects)
            {
                for (auto& complement : complements)
                {
                    // Temporarily written code
                    gameRules.AddBaseRule(subject->GetEffectType(),
                        obj->GetEffectType(), complement->GetEffectType());
                }
            }
        }
    }
}
}  // namespace Baba
