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

    Object& obj1 = game.Put(0, 0, "KEKE");
    Object& obj2 = game.Put(1, 1, "STAR");

    game.Put(2, 1, "TEXT_KEKE");
    game.Put(3, 1, "TEXT_IS");
    game.Put(4, 1, "TEXT_BABA");

    EXPECT_EQ(*game.FindBlocksByName(ObjectName::KEKE).at(0), obj1);
    EXPECT_EQ(*game.FindBlocksByName(ObjectName::STAR).at(0), obj2);

    game.ParseRules();

    game.ApplyRules();

    EXPECT_EQ(*game.FindBlocksByName(ObjectName::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindBlocksByName(ObjectName::STAR).at(0), obj2);
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
    // Do nothing
}

TEST(EffectTest, HOT)
{
    Game game(5, 5);
    
    game.Put(0, 0, "BABA");
    game.Put(0, 0, "KEKE");

    game.Put(2, 1, "TEXT_BABA");
    game.Put(3, 1, "TEXT_IS");
    game.Put(4, 1, "TEXT_MELT");

    game.Put(2, 2, "TEXT_KEKE");
    game.Put(3, 2, "TEXT_IS");
    game.Put(4, 2, "TEXT_HOT");
   
    game.ParseRules();
    game.ApplyRules();

    EXPECT_TRUE(game.FindObjectsByProperty(ObjectName::MELT).empty());
    EXPECT_EQ(game.At(0, 0).size(), 1);
    EXPECT_EQ(game.At(0, 0).at(0)->GetName(), ObjectName::KEKE);
}