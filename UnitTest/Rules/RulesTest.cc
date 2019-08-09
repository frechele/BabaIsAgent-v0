// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Common/Utils.h>
#include <Baba/Game/Game.h>
#include <Baba/Game/Object.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

using namespace Baba;
using namespace Utils;

// TEST(GameRulesTest, AddAndDeleteBaseRule)
// {
//     Game game(5, 5);
//     const int id = game.gameRules.AddBaseRule(ObjectName::BABA, ObjectName::IS, ObjectName::WORD);
    
//     EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetTarget(), ObjectName::BABA);
//     EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetVerb(), ObjectName::IS);
//     EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetEffect(), ObjectName::WORD);
//     EXPECT_EQ(game.gameRules.GetAllRules().begin()->GetRuleID(), id);

//     game.gameRules.DeleteRule(id);

//     EXPECT_TRUE(game.gameRules.GetAllRules().empty());
// }