// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Game/Object.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

using namespace Baba;

TEST(EffectTest, BABA)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE);
    Object& obj2 = game.Put(1, 1)
                       .SetType(ObjectType::STAR)
                       .SetEffectType(EffectType::STAR);

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::KEKE).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);

    game.gameRules.AddBaseRule(EffectType::KEKE, EffectType::IS, EffectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);
}

TEST(EffectTest, MELT)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);

    game.gameRules.AddBaseRule(EffectType::BABA, EffectType::IS, EffectType::MELT);

    game.ApplyRules();

    EXPECT_EQ(*game.FindObjectsByProperty(EffectType::MELT).at(0), obj1);
}

TEST(EffectTest, HOT)
{
    Game game(5, 5);
    
    game.Put(0, 0)
        .SetType(ObjectType::BABA)
        .SetEffectType(EffectType::BABA);
    game.Put(0, 0)
        .SetType(ObjectType::KEKE)
        .SetEffectType(EffectType::KEKE);
   
    game.gameRules.AddBaseRule(EffectType::BABA, EffectType::IS, EffectType::MELT);
    game.gameRules.AddBaseRule(EffectType::KEKE, EffectType::IS, EffectType::HOT);

    game.ApplyRules();

    EXPECT_TRUE(game.FindObjectsByProperty(EffectType::MELT).empty());
    EXPECT_EQ(game.At(0, 0).size(), 1);
    EXPECT_EQ(game.At(0, 0).at(0)->GetType(), ObjectType::KEKE);
}