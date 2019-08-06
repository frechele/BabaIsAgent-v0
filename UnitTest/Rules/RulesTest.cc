// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

using namespace Baba;

TEST(EnumTest, EffectToObject)
{
    EXPECT_EQ(EffectToObject(EffectType::BABA), ObjectType::BABA);
    EXPECT_EQ(EffectToObject(EffectType::KEKE), ObjectType::KEKE);
}

TEST(GameRulesTest, AddAndDeleteBaseRule)
{
    Game game(5, 5);
    const int id = game.gameRules_.AddBaseRule(ObjectType::BABA, "IS", EffectType::TEXT);
    
    EXPECT_EQ(game.gameRules_.rules_.begin()->target_, ObjectType::BABA);
    EXPECT_EQ(game.gameRules_.rules_.begin()->verb_, "IS");
    EXPECT_EQ(game.gameRules_.rules_.begin()->effect_, EffectType::TEXT);
    EXPECT_EQ(game.gameRules_.rules_.begin()->ruleID_, id);

    game.gameRules_.DeleteRule(id);

    EXPECT_TRUE(game.gameRules_.rules_.empty());
}