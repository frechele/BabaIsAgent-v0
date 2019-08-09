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

TEST(ObjectTest, SetName)
{
    using namespace Baba;

    Object object;

    EXPECT_EQ(object.SetName(ObjectName::BABA).GetName(), ObjectName::BABA);
    EXPECT_EQ(object.SetName(ObjectName::KEKE).GetName(), ObjectName::KEKE);
    EXPECT_ANY_THROW(object.SetName(ObjectName::INVALID));
}

TEST(ObjectTest, GetInfo)
{
    using namespace Baba;

    BlockInfo info = {ObjectName::BABA, WordClass::NOUN};
    Object object(info);
    
    EXPECT_EQ(object.GetName(), ObjectName::BABA);
    EXPECT_EQ(object.GetWordClass(), WordClass::NOUN);
    EXPECT_FALSE(object.IsText());
}

TEST(ObjectTest, GetProperty)
{
    using namespace Baba;

    Object object;
    EXPECT_TRUE(object.GetProperty().none());
}

TEST(ObjectTest, AddRemoveEnchant)
{
    using namespace Baba;

    Object object;
    object.AddEnchant(ObjectName::BABA, 0);
    
    EXPECT_TRUE(object.GetProperty().test(static_cast<std::size_t>(ObjectName::BABA)));

    object.RemoveEnchant(0);

    EXPECT_FALSE(object.GetProperty().test(static_cast<std::size_t>(ObjectName::BABA)));
}

TEST(ObjectTest, Destroy)
{
    using namespace Baba;

    Object object;

    EXPECT_NO_THROW(object.Destroy());
    EXPECT_EQ(object.IsDestroyed(), true);
    EXPECT_ANY_THROW(object.Destroy());
}
