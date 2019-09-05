// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Enums/Game.h>
#include <Baba/Game/Game.h>
#include <Baba/Rules/Effects.h>

#include <algorithm>
#include <stdexcept>

namespace Baba
{
Game::Game(std::size_t width, std::size_t height)
    : width_(width), height_(height), map_(width * height), ruleMap_(width * height)
{
    AddBaseRule(ObjectType::TEXT, ObjectType::IS, ObjectType::PUSH);
    AddBaseRule(ObjectType::TEXT, ObjectType::IS, ObjectType::WORD);
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
    return map_[pt2idx(x, y)];
}

bool Game::AtRule(std::size_t x, std::size_t y) const
{
    return ruleMap_[pt2idx(x, y)];
}

Object& Game::Put(std::size_t x, std::size_t y)
{
    objects_.emplace_back(new Object);
    map_[pt2idx(x, y)].emplace_back(objects_.back());

    return *map_[pt2idx(x, y)].back();
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

Object::Arr Game::FindObjects(std::function<bool(const Object&)> func,
                              bool excludeText) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (func(*obj))
            {
                if (!excludeText || !obj->IsText())
                {
                    result.emplace_back(obj);
                }
            }
        }
    }

    return result;
}

Object::Arr Game::FindObjectsByType(ObjectType type, bool excludeText) const
{
    std::function<bool(const Object&)> func;

    if (type == ObjectType::TEXT)
    {
        func = [](const Object& obj) { return obj.IsText(); };
        excludeText = false;
    }
    else
    {
        func = [type](const Object& obj) { return obj.GetType() == type; };
    }

    return FindObjects(func, excludeText);
}

Object::Arr Game::FindObjectsByProperty(PropertyType property,
                                        bool excludeText) const
{
    return FindObjects(
        [property](const Object& obj) { return obj.HasProperty(property); },
        excludeText);
}

Object::Arr Game::FindObjectsByPosition(const Object& target,
                                        bool excludeText) const
{
    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (*obj == target)
            {
                if (excludeText)
                {
                    Object::Arr arr;

                    for (auto& o : objs)
                    {
                        if (!o->IsText())
                        {
                            arr.emplace_back(o);
                        }
                    }

                    return arr;
                }
                else
                {
                    return objs;
                }
            }
        }
    }

    return Object::Arr();
}

Object::Arr Game::FilterObjectByFunction(
    const Object::Arr& objects, std::function<bool(const Object&)> func) const
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

const Game::Point Game::GetPositionByObject(const Object& target) const
{
    for (std::size_t y = 0; y < GetHeight(); y++)
    {
        for (std::size_t x = 0; x < GetWidth(); x++)
        {
            const auto& objs = map_[pt2idx(x, y)];

            for (auto& obj : objs)
            {
                if (*obj == target)
                {
                    return { x, y };
                }
            }
        }
    }

    throw std::runtime_error("Invalid target");
}

bool Game::ValidatePosition(std::size_t x, std::size_t y) const
{
    return x < width_ && y < height_;
}

void Game::Update(Action action)
{
    gameResult_ = GameResult::INVALID;
    nowAction_ = action;

    applyRules(baseRules_);
    parseRules();
    applyRules();

    parseRules();
    applyRules(rules_, false);

    determineResult();
}

GameResult Game::GetGameResult() const
{
    return gameResult_;
}

std::int64_t Game::AddRule(ObjectType target, ObjectType verb,
                           ObjectType effect)
{
    rules_.emplace(target, verb, effect);

    return Rule::CalcRuleID(target, verb, effect);
}

std::int64_t Game::AddBaseRule(ObjectType target, ObjectType verb,
                               ObjectType effect)
{
    baseRules_.emplace(target, verb, effect);

    return Rule::CalcRuleID(target, verb, effect);
}

void Game::RemoveRule(std::int64_t id)
{
    auto it =
        std::find_if(rules_.begin(), rules_.end(),
                     [id](const Rule& rule) { return rule.GetRuleID() == id; });

    if (it != rules_.end())
    {
        auto& rule = *it;
        auto targets = FindObjectsByType(rule.GetTarget(), true);

        if (IsPropertyType(rule.GetEffect()))
        {
            for (auto& target : targets)
            {
                target->RemoveProperty(ObjectToProperty(rule.GetEffect()));
            }
        }
        it = rules_.erase(it);
    }
}

const std::set<Rule>& Game::GetRules() const
{
    return rules_;
}

void Game::parseRules()
{
    std::fill(ruleMap_.begin(), ruleMap_.end(), false);

    while (!rules_.empty())
    {
        RemoveRule(rules_.begin()->GetRuleID());
    }

    auto verbs = FindObjects([](const Object& obj) {
        return IsVerbType(obj.GetType()) && obj.HasProperty(PropertyType::WORD);
    });

    for (auto& verb : verbs)
    {
        auto [x, y] = GetPositionByObject(*verb);

        const auto addRules = [&, x = x, y = y](std::size_t dx,
                                                std::size_t dy) {
            if (ValidatePosition(x - dx, y - dy) &&
                ValidatePosition(x + dx, y + dy))
            {
                auto targets = FilterObjectByFunction(
                    At(x - dx, y - dy), [](const Object& obj) {
                        return obj.HasProperty(PropertyType::WORD);
                    });
                auto effects = FilterObjectByFunction(
                    At(x + dx, y + dy), [](const Object& obj) {
                        return obj.HasProperty(PropertyType::WORD);
                    });

                for (auto& target : targets)
                {
                    for (auto& effect : effects)
                    {
                        AddRule(target->GetType(), verb->GetType(),
                                effect->GetType());
                    }
                }

                bool hasRule = (targets.size() > 0 && effects.size() > 0);
                ruleMap_[pt2idx(x - dx, y - dy)] =
                    ruleMap_[pt2idx(x - dx, y - dy)] | hasRule;
                ruleMap_[pt2idx(x + dx, y + dy)] =
                    ruleMap_[pt2idx(x + dx, y + dy)] | hasRule;
                ruleMap_[pt2idx(x, y)] = ruleMap_[pt2idx(x, y)] | hasRule;
            }
        };

        addRules(1, 0);
        addRules(0, 1);
    }
}

void Game::applyRules()
{
    applyRules(rules_);
}

void Game::applyRules(std::set<Rule>& r, bool doFunc)
{
    auto& effects = Effects::GetInstance().GetEffects();

    for (auto& rule : r)
    {
        if (rule.GetVerb() == ObjectType::IS)
        {
            auto targets = FindObjectsByType(rule.GetTarget(), true);

            if (IsObjectType(rule.GetEffect()))
            {
                for (auto& target : targets)
                {
                    target->SetType(rule.GetEffect());
                }
            }
            else
            {
                auto func = effects.at(ObjectToProperty(rule.GetEffect()));

                for (auto& target : targets)
                {
                    target->AddProperty(ObjectToProperty(rule.GetEffect()));
                    if (doFunc)
                    {
                        func(*this, *target);
                    }
                }
            }
        }
        // else if (rule.GetVerb() == ObjectType::HAS)
        //{
        //    // Not implemented yet
        //}
        // else if (rule.GetVerb() == ObjectType::MAKE)
        //{
        //    // Not implemented yet
        //}
        // else
        //{
        //    // throw
        //}
    }
}

void Game::determineResult()
{
    auto targets = FindObjectsByProperty(PropertyType::YOU);

    if (targets.empty())
    {
        gameResult_ = GameResult::DEFEAT;
        return;
    }

    for (auto& target : targets)
    {
        auto objs = FindObjectsByPosition(*target);

        for (auto& obj : objs)
        {
            if (obj->HasProperty(PropertyType::WIN))
            {
                gameResult_ = GameResult::WIN;
                return;
            }
        }
    }

    gameResult_ = GameResult::INVALID;
}

Object::Arr Game::TieStuckMoveableObjects(Object& pusher, Direction dir) const
{
    Object::Arr result;
    result.push_back(&pusher);

    auto [dx, dy] = dir2Vec(dir);
    auto pos = GetPositionByObject(pusher);
    std::size_t x = std::get<0>(pos);
    std::size_t y = std::get<1>(pos);

    while (ValidatePosition(x += dx, y += dy))
    {
        auto objs = At(x, y);

        if (objs.empty())
        {
            break;
        }

        if (!FilterObjectByFunction(objs,
                                    [](const Object& obj) -> bool {
                                        return obj.HasProperty(
                                            PropertyType::STOP);
                                    })
                 .empty())
        {
            return Object::Arr();
        }

        auto filtered =
            FilterObjectByFunction(objs, [](const Object& obj) -> bool {
                return obj.HasProperty(PropertyType::PUSH);
            });

        if (filtered.empty())
        {
            break;
        }

        result.insert(result.begin(), filtered.begin(), filtered.end());
    }

    return ValidatePosition(x, y) ? result : Object::Arr();
}

void Game::MoveObjects(const Object::Arr& objects, Direction dir)
{
    for (auto& obj : objects)
    {
        auto [dx, dy] = dir2Vec(dir);
        auto [x, y] = GetPositionByObject(*obj);
        auto& box = map_[pt2idx(x, y)];

        box.erase(std::find(box.begin(), box.end(), obj));

        map_[pt2idx(x + dx, y + dy)].push_back(obj);
        obj->SetDirection(dir);
    }
}

Action Game::GetNowAction() const
{
    return nowAction_;
}

Game::Point Game::dir2Vec(Direction dir) const
{
    switch (dir)
    {
        case Direction::UP:
            return Game::Point(0, -1);
        case Direction::DOWN:
            return Game::Point(0, 1);
        case Direction::LEFT:
            return Game::Point(-1, 0);
        case Direction::RIGHT:
            return Game::Point(1, 0);
        default:
            throw std::runtime_error("Invalid Direction");
    }
}

std::size_t Game::pt2idx(std::size_t x, std::size_t y) const
{
    return x + y * width_;
}
}  // namespace Baba
