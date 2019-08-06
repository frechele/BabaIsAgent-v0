// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rules.h>

#include <algorithm>

namespace Baba
{
const std::list<Rule>& GameRules::GetAllRules()
{
    return rules_;
}

int GameRules::GetRuleCount() const
{
    return ruleCount_;
}

int GameRules::AddBaseRule(ObjectType target, const std::string_view& verb,
                           EffectType effect)
{
    ++ruleCount_;
    rules_.emplace_back(target, verb, effect, ruleCount_);
    return ruleCount_;
}

void GameRules::DeleteRule(int ruleID)
{
    auto predicate = [ruleID](const Rule& rule) -> bool {
        return rule.ruleID == ruleID;
    };
    rules_.erase(std::remove_if(rules_.begin(), rules_.end(), predicate),
                 rules_.end());
}
}  // namespace Baba
