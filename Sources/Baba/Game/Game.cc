// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Common/Utils.h>
#include <Baba/Enums/Game.h>
#include <Baba/Game/Game.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

#include <algorithm>
#include <stdexcept>
#include <string_view>
#include <map>

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

Object& Game::Put(std::size_t x, std::size_t y, std::string_view name)
{
    BlockInfo info;
   
    // Find TEXT_
    if (name.find("TEXT_") != std::string_view::npos)
    {
        info.isTextObject = true;
        name.remove_prefix(5);
    }

    for (std::size_t i = 0; i < static_cast<std::size_t>(ObjectName::COUNT); ++i)
    {
        if (name == OBJECT_NAME_STR[i])
        {
            info.name = ObjectName(i);
        }
    }

    static std::vector wordClasses(
        {WordClass::NOUN, WordClass::VERB, WordClass::PROPERTY, WordClass::UNIQUE}); 
    static std::vector wordClassStrs(
        {NOUN_TYPE_STR, VERB_TYPE_STR, PROPERTY_TYPE_STR, UNIQUE_TYPE_STR});

    for (std::size_t i = 0; i < wordClasses.size(); i++)
    {
        if (std::find(wordClassStrs[i].begin(), wordClassStrs[i].end(), name) != wordClassStrs[i].end())
        {
            info.wordClass = wordClasses[i];
        }
    }

    objects_.emplace_back(new Object(info));

    if (objects_.back()->IsText())
    {
        objects_.back()->AddEnchant(ObjectName::WORD, -1);
        objects_.back()->AddEnchant(ObjectName::PUSH, -2);
    }

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

Object::Arr Game::FindObjectsByName(ObjectName name) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (obj->GetName() == name)
            {
                result.emplace_back(obj);
            }
        }
    }

    return result;
}

Object::Arr Game::FindBlocksByName(ObjectName name) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (obj->GetName() == name &&
                !obj->IsText())
            {
                result.emplace_back(obj);
            }
        }
    }

    return result;
}

Object::Arr Game::FindObjectsByUnique(ObjectName name) const
{
    Object::Arr result;

    if (name == ObjectName::TEXT)
    {
        for (auto& objs : map_)
        {
            for (auto& obj : objs)
            {
                if (obj->IsText())
                {
                    result.emplace_back(obj);
                }
            }
        }
    }

    return result;
}

Object::Arr Game::FindObjectsByProperty(ObjectName property) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (auto& obj : objs)
        {
            if (obj->GetProperty().test(static_cast<std::size_t>(property)))
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

const Game::Point Game::GetPositionByObject(const Object& target) const
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
    
    auto GetTargets = [&](auto rule)->auto{
        std::vector<Object*> targets;

        if (rule.GetTarget().GetWordClass() == WordClass::UNIQUE)
        {
            targets = FindObjectsByUnique(rule.GetTarget().GetName());
        }
        else
        {
            targets = FindBlocksByName(rule.GetTarget().GetName());
        }

        return targets;
    };

    for (auto& rule : rules)
    {
        auto ruleID = rule.GetRuleID();

        if (validRules_.at(ruleID) == RuleState::VALID)
        {
            continue;
        }

        if (rule.GetVerb().GetName() == ObjectName::IS)
        {
            std::vector<Object*> targets = GetTargets(rule);
            
            for (auto& target : targets)
            {
                if (validRules_.at(ruleID) == RuleState::NEW)
                {
                    target->AddEnchant(rule.GetEffect().GetName(), ruleID);
                }
                else
                {
                    target->RemoveEnchant(ruleID);
                    gameRules.DeleteRule(ruleID);
                }
            }
        }
    }

    for (auto& rule : rules)
    {
        if (rule.GetVerb().GetName() == ObjectName::IS)
        {
            std::vector<Object*> targets = GetTargets(rule);

            for (auto& target : targets)
            {
                auto func = effects.at(rule.GetEffect().GetName());
                func(*this, *target, rule);
            }
        }
    }

    for (auto i = validRules_.begin(); i != validRules_.end();)
    {
        if (i->second == RuleState::INVALID)
        {
            i = validRules_.erase(i);
        }
        else
        {
            ++i;
        }
    }
}

bool Game::ValidatePosition(std::size_t x, std::size_t y) const
{
    return x < width_ && y < height_;
}

void Game::ParseRules()
{
    // Init validRules_
    for (auto& rule : validRules_)
    {
        rule.second = RuleState::INVALID;
    }

    // Find verbs
    std::vector<std::tuple<Object*, Point>> verbs;

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

    constexpr std::tuple<std::size_t, std::size_t> vec[] = {{1, 0}, {0, 1}};

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

            // Validate rule or Make new rule
            for (auto& subject : subjects)
            {
                bool validateFlag = false;
                for (auto& complement : complements)
                {
                    // Check aleady existing
                    for (const auto& rule : gameRules.GetAllRules())
                    {
                        if (rule.GetTarget() == *subject &&
                            rule.GetVerb() == *obj &&
                            rule.GetEffect() == *complement)
                        {
                            validateFlag = true;
                            validRules_.at(rule.GetRuleID()) = RuleState::VALID;   
                        }
                    }
                    if (validateFlag)
                    {
                        break;
                    }
                    auto id = gameRules.AddBaseRule(*subject, *obj, *complement);
                    validRules_.emplace(id, RuleState::NEW);
                }
            }
        }
    }
}

void Game::DetermineResult()
{
    auto targets = FindObjectsByProperty(ObjectName::YOU);
    
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
            if (obj->GetProperty().test(static_cast<std::size_t>(ObjectName::WIN)))
            {
                gameResult_ = GameResult::WIN;
                return;
            }
        }
    }

    gameResult_ = GameResult::INVALID;
}

GameResult Game::GetGameResult() const
{
    return gameResult_;
}
}  // namespace Baba
