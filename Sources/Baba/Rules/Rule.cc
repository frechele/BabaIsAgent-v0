// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

namespace Baba
{
Rule::Rule(ObjectType target, std::string_view verb, EffectType effect, int ruleID)
    : target_(target), verb_(verb), effect_(effect), ruleID_(ruleID)
{
    // Do nothing
}
}  // namespace Baba