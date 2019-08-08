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
    
    game.Put(0, 0)
        .SetType(ObjectType::BABA)
        .SetEffectType(EffectType::BABA);
    Object& obj2 = game.Put(0, 0)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE)
                       .SetEffects({ EffectType::WORD });

    EXPECT_EQ(*game.FindObjectsByProperty(EffectType::WORD).at(0), obj2);
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

TEST(GameTest, GetPositionByObject)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);

    Object& obj2 = game.Put(4, 4)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);

    auto [x1, y1] = game.GetPositionByObject(obj1);
    auto [x2, y2] = game.GetPositionByObject(obj2);

    EXPECT_EQ(x1, 0);
    EXPECT_EQ(y1, 0);
    EXPECT_EQ(x2, 4);
    EXPECT_EQ(y2, 4);
}

TEST(GameTest, ParseRules_Vertical_Center)
{
    Game game(10, 10);

    Object& obj1 = game.Put(1, 1)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE);
    Object& obj2 = game.Put(5, 5)
                       .SetType(ObjectType::TEXT_KEKE)
                       .SetEffectType(EffectType::KEKE)
                       .SetEffect(EffectType::WORD);
    Object& obj3 = game.Put(6, 5)
                       .SetType(ObjectType::TEXT_IS)
                       .SetEffectType(EffectType::IS)
                       .SetEffect(EffectType::WORD);
    Object& obj4 = game.Put(7, 5)
                       .SetType(ObjectType::TEXT_BABA)
                       .SetEffectType(EffectType::BABA)
                       .SetEffect(EffectType::WORD);

    (void)obj1;
    (void)obj2;
    (void)obj3;
    (void)obj4;

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 1);

    auto& rule = *game.gameRules.GetAllRules().begin();

    EXPECT_EQ(rule.GetTarget(), ObjectType::KEKE);
    EXPECT_EQ(rule.GetVerb(), VerbType::IS);
    EXPECT_EQ(rule.GetEffect(), EffectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::BABA);
}

TEST(GameTest, ParseRules_Horizontal_Center)
{
    Game game(10, 10);

    Object& obj1 = game.Put(1, 1)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE);
    Object& obj2 = game.Put(5, 5)
                       .SetType(ObjectType::TEXT_KEKE)
                       .SetEffectType(EffectType::KEKE)
                       .SetEffect(EffectType::WORD);
    Object& obj3 = game.Put(5, 6)
                       .SetType(ObjectType::TEXT_IS)
                       .SetEffectType(EffectType::IS)
                       .SetEffect(EffectType::WORD);
    Object& obj4 = game.Put(5, 7)
                       .SetType(ObjectType::TEXT_BABA)
                       .SetEffectType(EffectType::BABA)
                       .SetEffect(EffectType::WORD);

    (void)obj1;
    (void)obj2;
    (void)obj3;
    (void)obj4;

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 1);

    auto& rule = *game.gameRules.GetAllRules().begin();

    EXPECT_EQ(rule.GetTarget(), ObjectType::KEKE);
    EXPECT_EQ(rule.GetVerb(), VerbType::IS);
    EXPECT_EQ(rule.GetEffect(), EffectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::BABA);
}

TEST(GameTest, ParseRules_Cross)
{
    Game game(10, 10);

    Object& obj1 = game.Put(1, 1)
                       .SetType(ObjectType::KEKE)
                       .SetEffectType(EffectType::KEKE);
    Object& obj2 = game.Put(5, 4)
                       .SetType(ObjectType::TEXT_KEKE)
                       .SetEffectType(EffectType::KEKE)
                       .SetEffect(EffectType::WORD);
    Object& obj3 = game.Put(5, 5)
                       .SetType(ObjectType::TEXT_IS)
                       .SetEffectType(EffectType::IS)
                       .SetEffect(EffectType::WORD);
    Object& obj4 = game.Put(5, 6)
                       .SetType(ObjectType::TEXT_HOT)
                       .SetEffectType(EffectType::HOT)
                       .SetEffect(EffectType::WORD);
    Object& obj5 = game.Put(4, 5)
                       .SetType(ObjectType::TEXT_BABA)
                       .SetEffectType(EffectType::BABA)
                       .SetEffect(EffectType::WORD);
    Object& obj6 = game.Put(6, 5)
                       .SetType(ObjectType::TEXT_MELT)
                       .SetEffectType(EffectType::MELT)
                       .SetEffect(EffectType::WORD);      
    Object& obj7 = game.Put(1, 1)
                       .SetType(ObjectType::BABA)
                       .SetEffectType(EffectType::BABA);  

    (void)obj1;
    (void)obj2;
    (void)obj3;
    (void)obj4;
    (void)obj5;
    (void)obj6;
    (void)obj7;

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 2);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::KEKE);
    EXPECT_TRUE(game.FindObjectsByType(ObjectType::BABA).empty());
}