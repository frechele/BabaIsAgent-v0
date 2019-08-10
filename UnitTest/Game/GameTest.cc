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

    game.Put(0, 0).SetType(ObjectType::BABA);
    game.Put(0, 0).SetType(ObjectType::KEKE);

    EXPECT_EQ(game.At(0, 0).at(0)->GetType(), ObjectType::BABA);
    EXPECT_EQ(game.At(0, 0).at(1)->GetType(), ObjectType::KEKE);
}

TEST(GameTest, FindObjectByType)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::BABA);
    Object& obj2 = game.Put(0, 0).SetType(ObjectType::KEKE);

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::KEKE).at(0), obj2);
}

TEST(GameTest, FindObjectsByProperty)
{
    Game game(5, 5);

    game.Put(0, 0).SetType(ObjectType::BABA);
    Object& obj2 = game.Put(0, 0)
                       .SetType(ObjectType::KEKE)
                       .AddProperty(PropertyType::WORD);

    EXPECT_EQ(*game.FindObjectsByProperty(PropertyType::WORD).at(0), obj2);
}

TEST(GameTest, FindObjectsByPosition)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::BABA);
    Object& obj2 = game.Put(0, 0).SetType(ObjectType::KEKE);

    EXPECT_EQ(*game.FindObjectsByPosition(obj1).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByPosition(obj1).at(1), obj2);

    Object invalid;
    EXPECT_EQ(game.FindObjectsByPosition(invalid).empty(), true);
}

TEST(GameTest, GetPositionByObject)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0).SetType(ObjectType::BABA);

    Object& obj2 = game.Put(4, 4).SetType(ObjectType::BABA);

    auto [x1, y1] = game.GetPositionByObject(obj1);
    auto [x2, y2] = game.GetPositionByObject(obj2);

    EXPECT_EQ(x1, 0);
    EXPECT_EQ(y1, 0);
    EXPECT_EQ(x2, 4);
    EXPECT_EQ(y2, 4);

    Object invalid;
    EXPECT_ANY_THROW(game.GetPositionByObject(invalid));
}

TEST(GameTest, ParseRules_Vertical_Center)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::KEKE);
    game.Put(5, 5)
        .SetType(ObjectType::KEKE)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(6, 5)
        .SetType(ObjectType::IS)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(7, 5)
        .SetType(ObjectType::BABA)
        .SetText(true)
        .AddProperty(PropertyType::WORD);

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 1);

    auto& rule = *game.gameRules.GetAllRules().begin();

    EXPECT_EQ(rule.GetTarget(), ObjectType::KEKE);
    EXPECT_EQ(rule.GetVerb(), ObjectType::IS);
    EXPECT_EQ(rule.GetEffect(), ObjectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::BABA);
}

TEST(GameTest, ParseRules_Horizontal_Center)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::KEKE);
    game.Put(5, 5)
        .SetType(ObjectType::KEKE)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 6)
        .SetType(ObjectType::IS)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 7)
        .SetType(ObjectType::BABA)
        .SetText(true)
        .AddProperty(PropertyType::WORD);

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 1);

    auto& rule = *game.gameRules.GetAllRules().begin();

    EXPECT_EQ(rule.GetTarget(), ObjectType::KEKE);
    EXPECT_EQ(rule.GetVerb(), ObjectType::IS);
    EXPECT_EQ(rule.GetEffect(), ObjectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::BABA);
}

TEST(GameTest, ParseRules_Cross)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::KEKE);
    game.Put(5, 4)
        .SetType(ObjectType::KEKE)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 5)
        .SetType(ObjectType::IS)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 6)
        .SetType(ObjectType::HOT)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(4, 5)
        .SetType(ObjectType::BABA)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(6, 5)
        .SetType(ObjectType::MELT)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(1, 1).SetType(ObjectType::BABA);

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 2);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::KEKE);
    EXPECT_TRUE(game.FindObjectsByType(ObjectType::BABA).empty());
}

TEST(GameTest, DetermineResult_WIN)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);
    game.Put(1, 1).SetType(ObjectType::FLAG);
    game.Put(5, 5)
        .SetType(ObjectType::BABA)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 6)
        .SetType(ObjectType::IS)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 7)
        .SetType(ObjectType::YOU)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(6, 5)
        .SetType(ObjectType::FLAG)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(6, 6)
        .SetType(ObjectType::IS)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(6, 7)
        .SetType(ObjectType::WIN)
        .SetText(true)
        .AddProperty(PropertyType::WORD);

    game.ParseRules();
    game.ApplyRules();
    game.DetermineResult();

    EXPECT_EQ(game.GetGameResult(), GameResult::WIN);
}

TEST(GameTest, DetermineResult_DEFEAT)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);

    game.ParseRules();
    game.ApplyRules();
    game.DetermineResult();

    EXPECT_EQ(game.GetGameResult(), GameResult::DEFEAT);
}

TEST(GameTest, DetermineResult_INVALID)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);
    game.Put(5, 5)
        .SetType(ObjectType::BABA)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 6)
        .SetType(ObjectType::IS)
        .SetText(true)
        .AddProperty(PropertyType::WORD);
    game.Put(5, 7)
        .SetType(ObjectType::YOU)
        .SetText(true)
        .AddProperty(PropertyType::WORD);

    game.ParseRules();
    game.ApplyRules();
    game.DetermineResult();

    EXPECT_EQ(game.GetGameResult(), GameResult::INVALID);
}