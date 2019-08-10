// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rules.h>

#include <algorithm>

namespace Baba
{
const std::list<Rule>& Rules::GetAllRules()
{
    return rules_;
}

std::int64_t Rules::AddBaseRule(ObjectType target, ObjectType verb, ObjectType effect)
{
    rules_.emplace_back(target, verb, effect);
    return rules_.back().GetRuleID();
}

void Rules::DeleteRule(int ruleID)
{
    auto predicate = [ruleID](const Rule& rule) -> bool {
        return rule.GetRuleID() == ruleID;
    };
    rules_.erase(std::remove_if(rules_.begin(), rules_.end(), predicate),
                 rules_.end());
}
}  // namespace Baba
