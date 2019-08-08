// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Common/Utils.h>
#include <Baba/Game/Game.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

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

void Game::ParseRules()
{
    // Find verbs
    std::vector<std::tuple<Object*, Pos>> verbs;

    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            auto type = obj->GetType();
            if (type == ObjectType::TEXT_IS || 
                type == ObjectType::TEXT_HAS ||
                type == ObjectType::TEXT_MAKE)
            {
                if (obj->GetEffects().test(static_cast<std::size_t>(EffectType::WORD)))
                {
                    verbs.emplace_back(obj, GetPositionByObject(*obj));
                }
            }
        }
    }

    static std::size_t dx[] = {1, 0};
    static std::size_t dy[] = {0, 1};

    // Syntax analyzing
    // The syntax currently implemented is:
    // 3 words:
    // - NOUN VERB NOUN
    // - NOUN VERB PROPERTY
    for (auto& verb : verbs)
    {
        // [i == 0]: Read from left to right
        // [i == 1]: Read from up to down
        for (std::size_t i = 0; i < 2; ++i)
        {
            const auto [obj, pos] = verb;
            auto [x, y] = pos;
            
            // Check out of bounds
            if ((x - dx[i]) < 0 || (y - dy[i]) < 0 ||
                (x + dx[i]) >= width_ || (y + dy[i]) >= height_)
            {
                continue;
            }

            // Check syntax
            Object::Arr subjects;
            Object::Arr complements;

            for (auto& subject : At(x - dx[i], y - dy[i]))
            {
                if (subject->GetEffects().test(static_cast<std::size_t>(EffectType::WORD)) &&
                    subject->GetWordClass() == WordClass::NOUN)
                {
                    subjects.emplace_back(subject);
                }
            }

            for (auto& complement : At(x + dx[i], y + dy[i]))
            {
                if (complement->GetEffects().test(static_cast<std::size_t>(EffectType::WORD)) &&
                    (complement->GetWordClass() == WordClass::NOUN ||
                     complement->GetWordClass() == WordClass::PROPERTY))
                {
                    complements.emplace_back(complement);
                }
            }

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
                    gameRules.AddBaseRule(Utils::EffectToObject(subject->GetEffectType()), VerbType::IS, complement->GetEffectType());
                }
            }
        }
    }
}
}  // namespace Baba
