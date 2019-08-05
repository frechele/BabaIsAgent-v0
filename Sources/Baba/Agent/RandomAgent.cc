// Copyright(c) 2019 Junyeong Park

#include <Baba/Agent/RandomAgent.h>

#include <effolkronium/random.hpp>

namespace Baba
{
Action RandomAgent::GetAction([[maybe_unused]]const Game& state)
{
    using Random = effolkronium::random_static;

    return static_cast<Action>(
        Random::get(0, static_cast<int>(Action::COUNT) - 1));
}
}  // namespace Baba
