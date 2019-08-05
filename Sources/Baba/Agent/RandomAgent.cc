// Copyright(c) 2019 Junyeong Park

#include <Baba/Agent/RandomAgent.h>

#include <effolkronium/random.hpp>

namespace Baba
{
Action RandomAgent::GetAction([[maybe_unused]]const Game& state)
{
    using Random = effolkronium::random_static;

    auto actions = { Action::UP, Action::DOWN, Action::LEFT, Action::RIGHT, Action::STAY };

    return Random::get(actions);
}
}  // namespace Baba
