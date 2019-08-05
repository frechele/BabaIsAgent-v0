// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rule.h>

namespace Baba
{
Rule::Rule(std::string_view target, std::string_view verb, std::string_view effect, int ruleID)
    : target_(target), verb_(verb), effect_(effect), ruleID_(ruleID)
{
    // Do nothing
}
}  // namespace Baba