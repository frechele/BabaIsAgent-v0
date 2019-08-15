// Copyright(C) 2019 Junyeong Park, Hyeonsu Kim

#include "gtest/gtest.h"

#include <Baba/Enums/ObjectType.h>

TEST(EnumTest, ObjectToProperty)
{
    using namespace Baba;

    EXPECT_EQ(ObjectToProperty(ObjectType::BABA), PropertyType::INVALID);
    EXPECT_EQ(ObjectToProperty(ObjectType::MELT), PropertyType::MELT);
}

TEST(EnumTest, PropertyToObject)
{
    using namespace Baba;

    EXPECT_EQ(PropertyToObject(PropertyType::MELT), ObjectType::MELT);
    EXPECT_EQ(PropertyToObject(PropertyType::HOT), ObjectType::HOT);

    EXPECT_EQ(PropertyToObject(PropertyType::INVALID), ObjectType::INVALID);
}