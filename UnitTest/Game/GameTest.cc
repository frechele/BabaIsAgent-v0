// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>

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
    ObjectBuilder builder;

    Object* obj1 = builder.Init()
                          .SetObjectType(ObjectType::BABA)
                          .SetEffectType(EffectType::BABA)
                          .Build();

    Object* obj2 = builder.Init()
                          .SetObjectType(ObjectType::KEKE)
                          .SetEffectType(EffectType::KEKE)
                          .Build();
    
    game.Put(0, 0, *obj1);
    game.Put(0, 0, *obj2);

    EXPECT_EQ(game.At(0, 0).at(0)->type_, ObjectType::BABA);
    EXPECT_EQ(game.At(0, 0).at(1)->type_, ObjectType::KEKE);
}

TEST(GameTest, FindObjectByType)
{
    Game game(5, 5);
    ObjectBuilder builder;

    Object* obj1 = builder.Init()
                          .SetObjectType(ObjectType::BABA)
                          .SetEffectType(EffectType::BABA)
                          .Build();

    Object* obj2 = builder.Init()
                          .SetObjectType(ObjectType::KEKE)
                          .SetEffectType(EffectType::KEKE)
                          .Build();
    
    game.Put(0, 0, *obj1);
    game.Put(0, 0, *obj2);

    EXPECT_EQ(game.FindObjectsByType(ObjectType::BABA).at(0), obj1);
    EXPECT_EQ(game.FindObjectsByType(ObjectType::KEKE).at(0), obj2);
}

TEST(GameTest, FindObjectsByProperty)
{
    Game game(5, 5);
    ObjectBuilder builder;

    Object* obj1 = builder.Init()
                          .SetObjectType(ObjectType::BABA)
                          .SetEffectType(EffectType::BABA)
                          .Build();

    Object* obj2 = builder.Init()
                          .SetObjectType(ObjectType::KEKE)
                          .SetEffectType(EffectType::KEKE)
                          .SetEffects({ EffectType::TEXT })
                          .Build();
    
    game.Put(0, 0, *obj1);
    game.Put(0, 0, *obj2);

    EXPECT_EQ(game.FindObjectsByProperty(EffectType::TEXT).at(0), obj2);
}