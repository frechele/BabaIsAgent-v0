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

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::KEKE);
    Object& obj2 = game.Put(1, 1).SetType(ObjectType::STAR);

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::KEKE).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);

    game.gameRules.AddBaseRule(ObjectType::KEKE, ObjectType::IS, ObjectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);
}

TEST(EffectTest, YOU)
{
    // Not implemented yet
}

TEST(EffectTest, WIN)
{
    // Do nothing
}

TEST(EffectTest, MELT)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::BABA);

    game.gameRules.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);

    game.ApplyRules();

    EXPECT_EQ(*game.FindObjectsByProperty(PropertyType::MELT).at(0), obj1);
}

TEST(EffectTest, HOT)
{
    Game game(5, 5);
    
    game.Put(0, 0).SetType(ObjectType::BABA);
    game.Put(0, 0).SetType(ObjectType::KEKE);
   
    game.gameRules.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);
    game.gameRules.AddBaseRule(ObjectType::KEKE, ObjectType::IS, ObjectType::HOT);

    game.ApplyRules();

    EXPECT_TRUE(game.FindObjectsByProperty(PropertyType::MELT).empty());
    EXPECT_EQ(game.At(0, 0).size(), 1);
    EXPECT_EQ(game.At(0, 0).at(0)->GetType(), ObjectType::KEKE);
}