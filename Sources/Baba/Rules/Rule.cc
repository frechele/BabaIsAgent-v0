// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

namespace Baba
{
Rule::Rule(ObjectType target, VerbType verb, EffectType effect, int ruleID)
    : target(target), verb(verb), effect(effect), ruleID(ruleID)
{
    // Do nothing
}

ObjectType Rule::GetTarget() const
{
    return target;
}

VerbType Rule::GetVerb() const
{
    return verb;
}

EffectType Rule::GetEffect() const
{
    return effect;
}

int Rule::GetRuleID() const
{
    return ruleID;
}
}  // namespace Baba