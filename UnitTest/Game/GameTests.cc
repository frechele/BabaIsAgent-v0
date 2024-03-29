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

TEST(GameTest, FindObjectByType_TEXT)
{
    Game game(5, 5);

    game.Put(0, 0).SetType(ObjectType::IS);
    game.Put(0, 0).SetType(ObjectType::KEKE).SetText(true);

    EXPECT_EQ(game.FindObjectsByType(ObjectType::TEXT).size(), 2);
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

    game.Put(0, 0).SetType(ObjectType::ME).SetText(true);

    EXPECT_EQ(game.FindObjectsByPosition(obj1, true).size(), 2u);

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
    game.Put(5, 5).SetType(ObjectType::KEKE).SetText(true);
    game.Put(6, 5).SetType(ObjectType::IS);
    game.Put(7, 5).SetType(ObjectType::BABA).SetText(true);

    game.Update();

    EXPECT_EQ(game.GetRules().size(), 1u);

    EXPECT_TRUE(game.AtRule(5, 5));
    EXPECT_TRUE(game.AtRule(6, 5));
    EXPECT_TRUE(game.AtRule(7, 5));
    EXPECT_FALSE(game.AtRule(8, 5));

    auto& rule = *game.GetRules().begin();

    EXPECT_EQ(rule.GetTarget(), ObjectType::KEKE);
    EXPECT_EQ(rule.GetVerb(), ObjectType::IS);
    EXPECT_EQ(rule.GetEffect(), ObjectType::BABA);

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::BABA);
}

TEST(GameTest, ParseRules_Horizontal_Center)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::KEKE);
    game.Put(5, 5).SetType(ObjectType::KEKE).SetText(true);
    game.Put(5, 6).SetType(ObjectType::IS);
    game.Put(5, 7).SetType(ObjectType::BABA).SetText(true);

    game.Update();

    EXPECT_EQ(game.GetRules().size(), 1u);
    
    EXPECT_TRUE(game.AtRule(5, 5));
    EXPECT_TRUE(game.AtRule(5, 6));
    EXPECT_TRUE(game.AtRule(5, 7));
    EXPECT_FALSE(game.AtRule(8, 5));

    auto& rule = *game.GetRules().begin();

    EXPECT_EQ(rule.GetTarget(), ObjectType::KEKE);
    EXPECT_EQ(rule.GetVerb(), ObjectType::IS);
    EXPECT_EQ(rule.GetEffect(), ObjectType::BABA);

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::BABA);
}

TEST(GameTest, ParseRules_Cross)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::KEKE);
    game.Put(5, 4).SetType(ObjectType::KEKE).SetText(true);
    game.Put(5, 5).SetType(ObjectType::IS);
    game.Put(5, 6).SetType(ObjectType::HOT);
    game.Put(4, 5).SetType(ObjectType::BABA).SetText(true);
    game.Put(6, 5).SetType(ObjectType::MELT);
    game.Put(1, 1).SetType(ObjectType::BABA);

    game.Update();

    EXPECT_EQ(game.GetRules().size(), 2u);

    EXPECT_TRUE(game.AtRule(5, 4));
    EXPECT_TRUE(game.AtRule(5, 5));
    EXPECT_TRUE(game.AtRule(5, 6));
    EXPECT_TRUE(game.AtRule(4, 5));
    EXPECT_TRUE(game.AtRule(6, 5));
    EXPECT_FALSE(game.AtRule(8, 5));

    EXPECT_EQ(game.At(1, 1).at(0)->GetType(), ObjectType::KEKE);
    EXPECT_TRUE(game.FindObjectsByType(ObjectType::BABA, true).empty());
}

TEST(GameTest, AddOrRemoveRule)
{
    Game game(5, 5);

    game.Put(1, 1).SetType(ObjectType::BABA);

    std::int64_t id =
        game.AddRule(ObjectType::BABA, ObjectType::IS, ObjectType::YOU);
    EXPECT_EQ(game.GetRules().size(), 1u);

    EXPECT_EQ(game.GetRules().begin()->GetRuleID(), id);

    EXPECT_EQ(game.GetRules().begin()->GetTarget(), ObjectType::BABA);
    EXPECT_EQ(game.GetRules().begin()->GetVerb(), ObjectType::IS);
    EXPECT_EQ(game.GetRules().begin()->GetEffect(), ObjectType::YOU);

    game.RemoveRule(id);
    EXPECT_FALSE(game.At(1, 1)[0]->HasProperty(PropertyType::YOU));
    EXPECT_EQ(game.GetRules().size(), 0u);
}

TEST(GameTest, checkGameOver)
{
    Game game(10, 10);

    game.Put(1, 1).SetType(ObjectType::BABA);

    game.AddRule(ObjectType::KEKE, ObjectType::IS, ObjectType::YOU);

    game.Update();
    EXPECT_EQ(game.GetGameResult(), GameResult::DEFEAT);
}

TEST(GameTest, determineResult_Push)
{
    Game game(10, 10);

    game.Put(5, 5).SetType(ObjectType::BABA);
    game.Put(4, 6).SetType(ObjectType::BABA).SetText(true);
    game.Put(5, 6).SetType(ObjectType::IS);
    game.Put(6, 6).SetType(ObjectType::YOU);

    game.Update(Action::STAY);
    EXPECT_EQ(game.GetGameResult(), GameResult::INVALID);

    game.Update(Action::DOWN);
    EXPECT_EQ(game.GetGameResult(), GameResult::DEFEAT);
}

TEST(GameTest, determineResult_Priority)
{
    Game game(10, 10);

    game.Put(5, 5).SetType(ObjectType::BABA);
    game.Put(5, 5).SetType(ObjectType::FLAG);
    game.Put(5, 6).SetType(ObjectType::FLAG);
    game.Put(4, 6).SetType(ObjectType::BABA).SetText(true);
    game.Put(5, 6).SetType(ObjectType::IS);
    game.Put(6, 6).SetType(ObjectType::YOU);

    game.AddBaseRule(ObjectType::FLAG, ObjectType::IS, ObjectType::WIN);

    game.Update(Action::STAY);
    EXPECT_EQ(game.GetGameResult(), GameResult::WIN);

    game.Update(Action::DOWN);
    EXPECT_EQ(game.GetGameResult(), GameResult::DEFEAT);
}

TEST(GameTest, MoveObject)
{
    Game game(10, 10);

    Object& obj = game.Put(5, 5).SetType(ObjectType::BABA);

    game.MoveObjects({ &obj }, Direction::DOWN);
    EXPECT_EQ(std::get<0>(game.GetPositionByObject(obj)), 5);
    EXPECT_EQ(std::get<1>(game.GetPositionByObject(obj)), 6);

    game.MoveObjects({ &obj }, Direction::LEFT);
    EXPECT_EQ(std::get<0>(game.GetPositionByObject(obj)), 4);
    EXPECT_EQ(std::get<1>(game.GetPositionByObject(obj)), 6);

    game.MoveObjects({ &obj }, Direction::UP);
    EXPECT_EQ(std::get<0>(game.GetPositionByObject(obj)), 4);
    EXPECT_EQ(std::get<1>(game.GetPositionByObject(obj)), 5);

    game.MoveObjects({ &obj }, Direction::RIGHT);
    EXPECT_EQ(std::get<0>(game.GetPositionByObject(obj)), 5);
    EXPECT_EQ(std::get<1>(game.GetPositionByObject(obj)), 5);
    EXPECT_EQ(obj.GetDirection(), Direction::RIGHT);

    EXPECT_ANY_THROW(game.MoveObjects({ &obj }, Direction::INVALID));
}