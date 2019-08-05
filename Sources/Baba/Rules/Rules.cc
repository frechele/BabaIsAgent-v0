// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Rules/Rules.h>

namespace Baba
{
GameRules& GameRules::GetInstance()
{
    static GameRules instance;
    return instance;
}

const int GameRules::AddBaseRule(ObjectType target, std::string_view verb, EffectType effect)
{
    rules_.emplace_back(target, verb, effect, ruleCount);
    ++ruleCount;
}

void GameRules::DeleteRule(const int& ruleID)
{
    for (auto i = rules_.begin(); i != rules_.end(); ++i)
    {
        if (i->ruleID_ == ruleID)
        {
            i = rules_.erase(i);
        }
        else
        {
            ++i;
        }
    }
}
}  // namespace Baba
