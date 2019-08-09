// Copyright (c) 2019 Junyeogn Park

#include "gtest/gtest.h"

#include <Baba/Game/Object.h>

TEST(ObjectTest, ID)
{
    using namespace Baba;

    Object obj1;
    Object obj2;

    EXPECT_EQ(obj2.GetID(), obj1.GetID() + 1);

    EXPECT_EQ(obj1 == obj1, true);
    EXPECT_EQ(obj1 != obj2, true);
}

TEST(ObjectTest, SetType)
{
    using namespace Baba;

    Object object;
    EXPECT_EQ(object.SetType(ObjectType::BABA).GetType(), ObjectType::BABA);
    EXPECT_EQ(object.SetType(ObjectType::KEKE).GetType(), ObjectType::KEKE);
    EXPECT_ANY_THROW(object.SetType(ObjectType::INVALID));
}

TEST(ObjectTest, SetEffectType)
{
    using namespace Baba;

    Object obj1;
    Object obj2;
    Object obj3;

    obj1.SetEffectType(EffectType::ALGAE);
    obj2.SetEffectType(EffectType::IS);
    obj3.SetEffectType(EffectType::HOT);

    EXPECT_EQ(obj1.GetWordClass(), WordClass::NOUN);
    EXPECT_EQ(obj2.GetWordClass(), WordClass::VERB);
    EXPECT_EQ(obj3.GetWordClass(), WordClass::PROPERTY);

    Object object;
    EXPECT_ANY_THROW(object.SetEffectType(EffectType::INVALID));
}

TEST(ObjectTest, Destroy)
{
    using namespace Baba;

    Object object;

    EXPECT_NO_THROW(object.Destroy());
    EXPECT_EQ(object.IsDestroyed(), true);
    EXPECT_ANY_THROW(object.Destroy());
}
