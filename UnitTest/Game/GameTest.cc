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

TEST(GameTest, Put_BLOCK)
{
    Game game(5, 5);

    game.Put(0, 0, "BABA");
    game.Put(0, 0, "KEKE");

    EXPECT_EQ(game.At(0, 0).at(0)->GetName(), ObjectName::BABA);
    EXPECT_EQ(game.At(0, 0).at(1)->GetName(), ObjectName::KEKE);
}

TEST(GameTest, Put_TEXT)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0, "TEXT_BABA");
    Object& obj2 = game.Put(0, 0, "TEXT_IS");
    Object& obj3 = game.Put(0, 0, "TEXT_YOU");
    Object& obj4 = game.Put(0, 0, "TEXT_TEXT");

    EXPECT_TRUE(obj1.IsText());
    EXPECT_TRUE(obj2.IsText());
    EXPECT_TRUE(obj3.IsText());
    EXPECT_TRUE(obj4.IsText());

    EXPECT_EQ(obj1.GetWordClass(), WordClass::NOUN);
    EXPECT_EQ(obj2.GetWordClass(), WordClass::VERB);
    EXPECT_EQ(obj3.GetWordClass(), WordClass::PROPERTY);
    EXPECT_EQ(obj4.GetWordClass(), WordClass::UNIQUE);

    EXPECT_TRUE(obj1.GetProperty().test(static_cast<std::size_t>(ObjectName::WORD)));
    EXPECT_TRUE(obj2.GetProperty().test(static_cast<std::size_t>(ObjectName::WORD)));
    EXPECT_TRUE(obj3.GetProperty().test(static_cast<std::size_t>(ObjectName::WORD)));
    EXPECT_TRUE(obj4.GetProperty().test(static_cast<std::size_t>(ObjectName::WORD)));

    EXPECT_TRUE(obj1.GetProperty().test(static_cast<std::size_t>(ObjectName::PUSH)));
    EXPECT_TRUE(obj2.GetProperty().test(static_cast<std::size_t>(ObjectName::PUSH)));
    EXPECT_TRUE(obj3.GetProperty().test(static_cast<std::size_t>(ObjectName::PUSH)));
    EXPECT_TRUE(obj4.GetProperty().test(static_cast<std::size_t>(ObjectName::PUSH)));
}

// TEST(GameTest, DestroyObject)
// {
//     Game game(5, 5);

//     Object& obj1 = game.Put(0, 0, "BABA");
//     Object& obj2 = game.Put(0, 0, "KEKE");

//     game.DestroyObject(obj1);

//     EXPECT_EQ(*game.At(0, 0).at(0), obj2);
// }

TEST(GameTest, FindObjectByName)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0, "BABA");
    Object& obj2 = game.Put(0, 0, "KEKE");

    EXPECT_EQ(*game.FindObjectsByName(ObjectName::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByName(ObjectName::KEKE).at(0), obj2);
}

TEST(GameTest, FindBlocksByName)
{
    Game game(5, 5);

    game.Put(0, 0, "BABA");
    game.Put(0, 0, "TEXT_KEKE");

    EXPECT_EQ(game.FindObjectsByName(ObjectName::BABA).size(), 1);
}

TEST(GameTest, FindObjectByUnique)
{
    Game game(5, 5);

    game.Put(0, 0, "BABA");
    Object& obj1 = game.Put(0, 0, "TEXT_KEKE");

    EXPECT_EQ(game.FindObjectsByUnique(ObjectName::TEXT).size(), 1);
    EXPECT_EQ(*game.FindObjectsByUnique(ObjectName::TEXT).at(0), obj1);
}

TEST(GameTest, FindObjectsByProperty)
{
    Game game(5, 5);

    game.Put(0, 0, "BABA");
    Object& obj2 = game.Put(0, 0, "KEKE").AddEnchant(ObjectName::WORD, 0);

    EXPECT_EQ(*game.FindObjectsByProperty(ObjectName::WORD).at(0), obj2);
}

TEST(GameTest, FindObjectsByPosition)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0, "BABA");
    Object& obj2 = game.Put(0, 0, "KEKE");

    EXPECT_EQ(*game.FindObjectsByPosition(obj1).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByPosition(obj1).at(1), obj2);

    Object invalid;
    EXPECT_EQ(game.FindObjectsByPosition(invalid).empty(), true);
}

TEST(GameTest, GetPositionByObject)
{
    Game game(5, 5);

    Object& obj1 = game.Put(0, 0, "BABA");

    Object& obj2 = game.Put(4, 4, "BABA");

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

    game.Put(1, 1, "KEKE");
    game.Put(5, 5, "TEXT_KEKE");
    game.Put(6, 5, "TEXT_IS");
    game.Put(7, 5, "TEXT_BABA");

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 1);

    auto& rule = *game.gameRules.GetAllRules().begin();

    EXPECT_EQ(rule.GetTarget().GetName(), ObjectName::KEKE);
    EXPECT_EQ(rule.GetVerb().GetName(), ObjectName::IS);
    EXPECT_EQ(rule.GetEffect().GetName(), ObjectName::BABA);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetName(), ObjectName::BABA);
}

TEST(GameTest, ParseRules_Horizontal_Center)
{
    Game game(10, 10);

    game.Put(1, 1, "KEKE");
    game.Put(5, 5, "TEXT_KEKE");
    game.Put(5, 6, "TEXT_IS");
    game.Put(5, 7, "TEXT_BABA");

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 1);

    auto& rule = *game.gameRules.GetAllRules().begin();

    EXPECT_EQ(rule.GetTarget().GetName(), ObjectName::KEKE);
    EXPECT_EQ(rule.GetVerb().GetName(), ObjectName::IS);
    EXPECT_EQ(rule.GetEffect().GetName(), ObjectName::BABA);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetName(), ObjectName::BABA);
}

TEST(GameTest, ParseRules_Cross)
{
    Game game(10, 10);

    game.Put(1, 1, "KEKE");
    game.Put(1, 1, "BABA");
    game.Put(5, 4, "TEXT_KEKE");
    game.Put(5, 5, "TEXT_IS");
    game.Put(5, 6, "TEXT_HOT");
    game.Put(4, 5, "TEXT_BABA");
    game.Put(6, 5, "TEXT_MELT");

    game.ParseRules();

    EXPECT_EQ(game.gameRules.GetRuleCount(), 2);

    game.ApplyRules();

    EXPECT_EQ(game.At(1, 1).at(0)->GetName(), ObjectName::KEKE);
    EXPECT_TRUE(game.FindBlocksByName(ObjectName::BABA).empty());
}

TEST(GameTest, DetermineResult_WIN)
{
    Game game(10, 10);

    game.Put(1, 1, "BABA");
    game.Put(1, 1, "FLAG");
    game.Put(5, 5, "TEXT_BABA");
    game.Put(5, 6, "TEXT_IS");
    game.Put(5, 7, "TEXT_YOU");
    game.Put(6, 5, "TEXT_FLAG");
    game.Put(6, 6, "TEXT_IS");
    game.Put(6, 7, "TEXT_WIN");

    game.ParseRules();
    game.ApplyRules();
    game.DetermineResult();

    EXPECT_EQ(game.GetGameResult(), GameResult::WIN);
}

TEST(GameTest, DetermineResult_DEFEAT)
{
    Game game(10, 10);

    game.Put(1, 1, "BABA");

    game.ParseRules();
    game.ApplyRules();
    game.DetermineResult();

    EXPECT_EQ(game.GetGameResult(), GameResult::DEFEAT);
}

TEST(GameTest, DetermineResult_INVALID)
{
    Game game(10, 10);

    game.Put(1, 1, "BABA");
    game.Put(5, 5, "TEXT_BABA");
    game.Put(5, 6, "TEXT_IS");
    game.Put(5, 7, "TEXT_YOU");

    game.ParseRules();
    game.ApplyRules();
    game.DetermineResult();

    EXPECT_EQ(game.GetGameResult(), GameResult::INVALID);
}