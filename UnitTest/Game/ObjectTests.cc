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

    EXPECT_TRUE(object.SetType(ObjectType::YOU).IsText());

    EXPECT_ANY_THROW(object.SetType(ObjectType::INVALID));
}

TEST(ObjectTest, SetText)
{
    using namespace Baba;

    Object object;
    object.SetType(ObjectType::BABA);

    EXPECT_FALSE(object.IsText());

    object.SetText(true);
    EXPECT_TRUE(object.IsText());

    object.SetType(ObjectType::IS);
    EXPECT_TRUE(object.IsText());

    EXPECT_ANY_THROW(object.SetText(false));
}

TEST(ObjectTest, Property)
{
    using namespace Baba;

    Object object;
    object.AddProperty(PropertyType::MELT);

    EXPECT_TRUE(object.HasProperty(PropertyType::MELT));

    object.RemoveProperty(PropertyType::MELT);

    EXPECT_FALSE(object.HasProperty(PropertyType::MELT));
}

TEST(ObjectTest, Destroy)
{
    using namespace Baba;

    Object object;

    EXPECT_NO_THROW(object.Destroy());
    EXPECT_EQ(object.IsDestroyed(), true);
    EXPECT_ANY_THROW(object.Destroy());
}
