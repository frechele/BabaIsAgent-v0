// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

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
    return Rule::GetRuleID(target_, verb_, effect_);
}

std::int64_t Rule::GetRuleID(ObjectType target, ObjectType verb,
                             ObjectType effect)
{
    return (static_cast<std::int64_t>(target) << 40) |
           (static_cast<std::int64_t>(verb) << 10) |
           (static_cast<std::int64_t>(effect) << 0);
}

bool Rule::operator<(const Rule& other) const
{
    return (GetRuleID() < other.GetRuleID());
}
}  // namespace Baba