// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

namespace Baba
{
Rule::Rule(ObjectType target, VerbType verb, EffectType effect, int ruleID)
    : target_(target), verb_(verb), effect_(effect), ruleID_(ruleID)
{
    // Do nothing
}

ObjectType Rule::GetTarget() const
{
    return target_;
}

VerbType Rule::GetVerb() const
{
    return verb_;
}

EffectType Rule::GetEffect() const
{
    return effect_;
}

int Rule::GetRuleID() const
{
    return ruleID_;
}
}  // namespace Baba