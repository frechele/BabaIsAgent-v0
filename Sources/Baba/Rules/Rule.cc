// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

namespace Baba
{
Rule::Rule(Object& target, Object& verb, Object& effect, int ruleID)
    : target_(&target), verb_(&verb), effect_(&effect), ruleID_(ruleID)
{
    // Do nothing
}

Object& Rule::GetTarget() const
{
    return *target_;
}

Object& Rule::GetVerb() const
{
    return *verb_;
}

Object& Rule::GetEffect() const
{
    return *effect_;
}

int Rule::GetRuleID() const
{
    return ruleID_;
}
}  // namespace Baba