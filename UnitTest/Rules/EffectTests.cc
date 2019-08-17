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

    game.AddBaseRule(ObjectType::KEKE, ObjectType::IS, ObjectType::BABA);

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

    game.Update(Action::RIGHT);
    EXPECT_EQ(game.At(2, 1).size(), 1);
    EXPECT_TRUE(game.At(1, 1).empty());

    game.Update(Action::DOWN);
    EXPECT_EQ(game.At(2, 2).size(), 1);
    EXPECT_TRUE(game.At(2, 1).empty());

    game.Update(Action::LEFT);
    EXPECT_EQ(game.At(1, 2).size(), 1);
    EXPECT_TRUE(game.At(2, 2).empty());

    game.Update(Action::UP);
    EXPECT_EQ(game.At(1, 1).size(), 1);
    EXPECT_TRUE(game.At(1, 2).empty());
}

TEST(EffectTest, PUSH)
{
    Game game(10, 10);

    game.Put(0, 1).SetType(ObjectType::KEY);
    game.Put(1, 1).SetType(ObjectType::BABA);
    game.Put(1, 1).SetType(ObjectType::KEKE);
    game.Put(2, 1).SetType(ObjectType::KEKE);
    game.Put(3, 1).SetType(ObjectType::ALGAE);
    game.Put(4, 1).SetType(ObjectType::IS);
    game.Put(1, 2).SetType(ObjectType::STAR);

    game.AddBaseRule(ObjectType::KEY, ObjectType::IS, ObjectType::PUSH);
    game.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::YOU);
    game.AddBaseRule(ObjectType::KEKE, ObjectType::IS, ObjectType::PUSH);
    game.AddBaseRule(ObjectType::ALGAE, ObjectType::IS, ObjectType::PUSH);
    game.AddBaseRule(ObjectType::STAR, ObjectType::IS, ObjectType::YOU);

    game.Update(Action::RIGHT);
    EXPECT_EQ(game.At(0, 1)[0]->GetType(), ObjectType::KEY);
    EXPECT_EQ(game.At(1, 1)[0]->GetType(), ObjectType::KEKE);
    EXPECT_EQ(game.At(2, 1)[0]->GetType(), ObjectType::BABA);
    EXPECT_EQ(game.At(3, 1)[0]->GetType(), ObjectType::KEKE);
    EXPECT_EQ(game.At(4, 1)[0]->GetType(), ObjectType::ALGAE);
    EXPECT_EQ(game.At(5, 1)[0]->GetType(), ObjectType::IS);
    EXPECT_EQ(game.At(2, 2)[0]->GetType(), ObjectType::STAR);
}

TEST(EffectTest, STOP)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);
    game.Put(2, 1).SetType(ObjectType::KEKE);
    game.Put(3, 1).SetType(ObjectType::ALGAE);
    game.Put(4, 1).SetType(ObjectType::WALL);

    game.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::YOU);
    game.AddBaseRule(ObjectType::KEKE, ObjectType::IS, ObjectType::PUSH);
    game.AddBaseRule(ObjectType::ALGAE, ObjectType::IS, ObjectType::PUSH);
    game.AddBaseRule(ObjectType::WALL, ObjectType::IS, ObjectType::STOP);

    game.Update(Action::RIGHT);
    EXPECT_EQ(game.At(1, 1)[0]->GetType(), ObjectType::BABA);
    EXPECT_EQ(game.At(2, 1)[0]->GetType(), ObjectType::KEKE);
    EXPECT_EQ(game.At(3, 1)[0]->GetType(), ObjectType::ALGAE);
    EXPECT_EQ(game.At(4, 1)[0]->GetType(), ObjectType::WALL);
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

    game.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);

    game.Update();

    EXPECT_EQ(*game.FindObjectsByProperty(PropertyType::MELT).at(0), obj1);
}

TEST(EffectTest, HOT)
{
    Game game(5, 5);
    
    game.Put(0, 0).SetType(ObjectType::BABA);
    game.Put(0, 0).SetType(ObjectType::KEKE);
   
    game.AddBaseRule(ObjectType::BABA, ObjectType::IS, ObjectType::MELT);
    game.AddBaseRule(ObjectType::KEKE, ObjectType::IS, ObjectType::HOT);

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