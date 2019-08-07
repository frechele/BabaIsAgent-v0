// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Game/Object.h>

using namespace Baba;

TEST(GameTest, GetHeighWidth)
{
    Game game(5, 10);

    EXPECT_EQ(game.GetHeight(), 10);
    EXPECT_EQ(game.GetWidth(), 5);
}

TEST(GameTest, Put)
{
    Game game(5, 5);
    
    game.Put(0, 0)
        .SetType(ObjectType::BABA)
        .SetEffectType(EffectType::BABA);
    game.Put(0, 0)
        .SetType(ObjectType::KEKE)
        .SetEffectType(EffectType::KEKE);

    EXPECT_EQ(game.At(0, 0).at(0)->GetType(), ObjectType::BABA);
    EXPECT_EQ(game.At(0, 0).at(1)->GetType(), ObjectType::KEKE);
}

TEST(GameTest, FindObjectByType)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);
    Object& obj2 = game.Put(0, 0)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE);

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::KEKE).at(0), obj2);
}

TEST(GameTest, FindObjectsByProperty)
{
    Game game(5, 5);
    
    [[maybe_unused]]
    Object& obj1 = game.Put(0, 0)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);
    Object& obj2 = game.Put(0, 0)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE)
                       .SetEffects({ EffectType::TEXT });

    EXPECT_EQ(*game.FindObjectsByProperty(EffectType::TEXT).at(0), obj2);
}

TEST(GameTest, FindObjectsByPosition)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);
    Object& obj2 = game.Put(0, 0)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE);

    EXPECT_EQ(*game.FindObjectsByPosition(obj1).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByPosition(obj1).at(1), obj2);
}