// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Game/Object.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

using namespace Baba;

TEST(GameRulesTest, AddAndDeleteBaseRule)
{
    Game game(5, 5);
    auto id = game.gameRules.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::WORD);

    EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetTarget(),
              ObjectType::BABA);
    EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetVerb(), ObjectType::IS);
    EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetEffect(),
              ObjectType::WORD);
    EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetRuleID(), id);

    game.gameRules.DeleteRule(id);

    EXPECT_TRUE(game.gameRules.GetAllRules().empty());
}