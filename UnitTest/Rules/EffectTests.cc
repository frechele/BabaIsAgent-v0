// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Game/Object.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>

using namespace Baba;

TEST(EffectTest, BABA)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::KEKE);
    Object& obj2 = game.Put(1, 1).SetType(ObjectType::STAR);

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::KEKE).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);

    game.AddRule(ObjectType::KEKE, ObjectType::IS, ObjectType::BABA);

    game.Update();

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);
}

TEST(EffectTest, YOU)
{
     Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);
    game.Put(5, 5)
        .SetType(ObjectType::BABA)
        .SetText(true);
    game.Put(5, 6).SetType(ObjectType::IS);
    game.Put(5, 7).SetType(ObjectType::YOU);

    game.Update();

    EXPECT_EQ(game.GetGameResult(), GameResult::INVALID);
}

TEST(EffectTest, WIN)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);
    game.Put(1, 1).SetType(ObjectType::FLAG);
    game.Put(5, 5)
        .SetType(ObjectType::BABA)
        .SetText(true);
    game.Put(5, 6).SetType(ObjectType::IS);
    game.Put(5, 7).SetType(ObjectType::YOU);
    game.Put(6, 5)
        .SetType(ObjectType::FLAG)
        .SetText(true);
    game.Put(6, 6).SetType(ObjectType::IS);
    game.Put(6, 7).SetType(ObjectType::WIN);

    game.Update();

    EXPECT_EQ(game.GetGameResult(), GameResult::WIN);
}

TEST(EffectTest, MELT)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::BABA);

    game.AddRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);

    game.Update();

    EXPECT_EQ(*game.FindObjectsByProperty(PropertyType::MELT).at(0), obj1);
}

TEST(EffectTest, HOT)
{
    Game game(5, 5);
    
    game.Put(0, 0).SetType(ObjectType::BABA);
    game.Put(0, 0).SetType(ObjectType::KEKE);
   
    game.AddRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);
    game.AddRule(ObjectType::KEKE, ObjectType::IS, ObjectType::HOT);

    game.Update();

    EXPECT_TRUE(game.FindObjectsByProperty(PropertyType::MELT).empty());
    EXPECT_EQ(game.At(0, 0).size(), 1);
    EXPECT_EQ(game.At(0, 0).at(0)->GetType(), ObjectType::KEKE);
}

TEST(EffectTest, Priority)
{
    Game game(5, 5);

    game.AddRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);
    game.AddRule(ObjectType::BABA, ObjectType::IS, ObjectType::YOU);
    game.AddRule(ObjectType::BABA, ObjectType::IS, ObjectType::YOU);
}