// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Effects.h>

namespace Baba
{
Rule::Rule(ObjectType target, ObjectType verb, ObjectType effect)
    : target_(target), verb_(verb), effect_(effect)
{
    // Do nothing
}

ObjectType Rule::GetTarget() const
{
    return target_;
}

ObjectType Rule::GetVerb() const
{
    return verb_;
}

ObjectType Rule::GetEffect() const
{
    return effect_;
}

std::int64_t Rule::GetRuleID() const
{
    return Rule::CalcRuleID(target_, verb_, effect_);
}

std::int64_t Rule::CalcRuleID(ObjectType target, ObjectType verb,
                             ObjectType effect)
{
    std::int64_t ruleID = 0;

    if (IsPropertyType(effect))
    {
        ruleID = static_cast<std::int64_t>(
                 Effects::GetInstance().GetPriority(ObjectToProperty(effect)));
    }

    return (ruleID << 54) |
           (static_cast<std::int64_t>(target) << 36) |
           (static_cast<std::int64_t>(verb) << 18) |
           (static_cast<std::int64_t>(effect) << 0);
}

bool Rule::operator<(const Rule& other) const
{
    return (GetRuleID() < other.GetRuleID());
}
}  // namespace Baba