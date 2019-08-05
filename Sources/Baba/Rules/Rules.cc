// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rules.h>

namespace Baba
{
const int GameRules::AddBaseRule(ObjectType target, std::string_view verb, EffectType effect)
{
    ++ruleCount;
    rules_.emplace_back(target, verb, effect, ruleCount);
    return ruleCount;
}

void GameRules::DeleteRule(const int& ruleID)
{
    for (auto i = rules_.begin(); i != rules_.end(); ++i)
    {
        if (i->ruleID_ == ruleID)
        {
            i = rules_.erase(i);
        }
        else if (i != rules_.end())
        {
            ++i;
        }
    }
}
}  // namespace Baba
