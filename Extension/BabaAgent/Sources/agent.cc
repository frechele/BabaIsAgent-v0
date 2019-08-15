// Copyright(C) 2019 Junyeong Park

#include <BabaAgent/agent.h>

namespace Baba
{
Action RLAgent::GetAction([[maybe_unused]]const Game& state)
{
    return Action::STAY;
}
}  // namespace Baba::Agent
