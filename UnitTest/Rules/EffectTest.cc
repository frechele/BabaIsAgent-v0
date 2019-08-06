// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>
#include <Baba/Rules/Effects.h>
#include <Baba/Rules/Rule.h>
#include <Baba/Rules/Rules.h>

using namespace Baba;

TEST(EffectTest, BABA)
{
    Game game(5, 5);
    ObjectBuilder builder;

    Object obj1 = builder.Init()
                         .SetObjectType(ObjectType::KEKE)
                         .SetEffectType(EffectType::KEKE)
                         .Build();

    Object obj2 = builder.Init()
                         .SetObjectType(ObjectType::STAR)
                         .SetEffectType(EffectType::STAR)
                         .Build();
    
    game.Put(0, 0, obj1);
    game.Put(1, 1, obj2);

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::KEKE).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);

    game.gameRules.AddBaseRule(ObjectType::KEKE, "IS", EffectType::BABA);

    game.ApplyRules();

    EXPECT_EQ(*game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(*game.FindObjectsByType(ObjectType::STAR).at(0), obj2);
}

TEST(EffectTest, MELT)
{
    Game game(5, 5);
    ObjectBuilder builder;

    Object obj1 = builder.Init()
                         .SetObjectType(ObjectType::BABA)
                         .SetEffectType(EffectType::BABA)
                         .Build();
    
    game.Put(0, 0, obj1);

    game.gameRules.AddBaseRule(ObjectType::BABA, "IS", EffectType::MELT);

    game.ApplyRules();

    EXPECT_EQ(*game.FindObjectsByProperty(EffectType::MELT).at(0), obj1);
}

TEST(EffectTest, HOT)
{
    Game game(5, 5);
    ObjectBuilder builder;

    Object obj1 = builder.Init()
                         .SetObjectType(ObjectType::BABA)
                         .SetEffectType(EffectType::BABA)
                         .Build();

    Object obj2 = builder.Init()
                         .SetObjectType(ObjectType::KEKE)
                         .SetEffectType(EffectType::KEKE)
                         .Build();

    game.Put(0, 0, obj1);
    game.Put(0, 0, obj2);

    game.gameRules.AddBaseRule(ObjectType::BABA, "IS", EffectType::MELT);
    game.gameRules.AddBaseRule(ObjectType::KEKE, "IS", EffectType::HOT);

    game.ApplyRules();

    EXPECT_TRUE(game.FindObjectsByProperty(EffectType::MELT).empty());
    EXPECT_EQ(game.At(0, 0).size(), 1);
    EXPECT_EQ(game.At(0, 0).at(0)->type, ObjectType::KEKE);
}