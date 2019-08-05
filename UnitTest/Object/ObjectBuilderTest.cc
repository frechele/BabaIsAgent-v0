// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>

using namespace Baba;

TEST(ObjectBuilder, BuildBlockTest)
{
    ObjectBuilder builder;
    Object* object = builder.Init()
                            .SetObjectType(ObjectType::BABA)
                            .SetEffectType(EffectType::BABA)
                            .Build();
    
    EXPECT_EQ(object->type_, ObjectType::BABA);
    EXPECT_EQ(object->effectType_, EffectType::BABA);
}

TEST(ObjectBuilder, BuildTextTest)
{
    ObjectBuilder builder;
    Object* object = builder.Init()
                            .SetObjectType(ObjectType::TEXT_BABA)
                            .SetEffectType(EffectType::BABA)
                            .SetEffects({ EffectType::TEXT })
                            .Build();
    
    EXPECT_EQ(object->type_, ObjectType::TEXT_BABA);
    EXPECT_EQ(object->effectType_, EffectType::BABA);
    EXPECT_TRUE(object->effects_.test(static_cast<std::size_t>(EffectType::TEXT)));
}