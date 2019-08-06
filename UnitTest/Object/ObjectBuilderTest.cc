// Copyright (c) 2019 Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>
#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>

using namespace Baba;

TEST(ObjectBuilderTest, BuildBlock)
{
    ObjectBuilder builder;
    Object object = builder.Init()
                            .SetObjectType(ObjectType::BABA)
                            .SetEffectType(EffectType::BABA)
                            .Build();
    
    EXPECT_EQ(object.type, ObjectType::BABA);
    EXPECT_EQ(object.effectType, EffectType::BABA);
}

TEST(ObjectBuilderTest, BuildText)
{
    ObjectBuilder builder;
    Object object = builder.Init()
                            .SetObjectType(ObjectType::TEXT_BABA)
                            .SetEffectType(EffectType::BABA)
                            .SetEffects({ EffectType::TEXT })
                            .Build();
    
    EXPECT_EQ(object.type, ObjectType::TEXT_BABA);
    EXPECT_EQ(object.effectType, EffectType::BABA);
    EXPECT_TRUE(object.GetEffects().test(static_cast<std::size_t>(EffectType::TEXT)));
}