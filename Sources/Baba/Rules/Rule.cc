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
    return (static_cast<std::int64_t>(target_) << 40) 
        | (static_cast<std::int64_t>(verb_) << 10) 
        | (static_cast<std::int64_t>(effect_) << 0);
}
}  // namespace Baba