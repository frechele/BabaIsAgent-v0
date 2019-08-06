// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rules.h>

#include <algorithm>

namespace Baba
{
const int GameRules::AddBaseRule(ObjectType target, std::string_view verb, EffectType effect)
{
    ++ruleCount;
    rules_.emplace_back(target, verb, effect, ruleCount);
    return ruleCount;
}

void GameRules::DeleteRule(const int& ruleID)
{
    auto predicate = [ruleID](const Rule& rule)->bool{
        return rule.ruleID_ == ruleID;
    };
    rules_.erase(std::remove_if(rules_.begin(), rules_.end(), predicate), rules_.end());
}
}  // namespace Baba
