// Copyright(c) 2019 Junyeong Park

#include "gtest/gtest.h"

#include <Baba/Agent/RandomAgent.h>
#include <Baba/Game/Game.h>

TEST(RandomAgent, GetAction)
{
    using namespace Baba;

    Game game(5, 5);

    RandomAgent agent;
    
    std::vector<Action> actions = { Action::UP, Action::DOWN, Action::LEFT, Action::RIGHT, Action::STAY };
    Action action = agent.GetAction(game);
    
    EXPECT_NE(std::find(begin(actions), end(actions), action), end(actions));
}
