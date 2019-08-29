// Copyright(C) 2019 Junyeong Park

#include "gtest/gtest.h"

#include <Baba/Agent/Preprocess.h>

TEST(Preprocess, StateToTensor)
{
    using namespace Baba;

    Game game1(10, 10);

    std::vector<float> tensor;

    tensor = Preprocess::StateToTensor(game1);
    EXPECT_EQ(tensor.size(),
              Preprocess::TENSOR_DIM * game1.GetWidth() * game1.GetHeight());

    {
        Game game2(40, 40);

        tensor = Preprocess::StateToTensor(game2);
        EXPECT_EQ(tensor.size(), Preprocess::TENSOR_DIM * game2.GetWidth() *
                                     game2.GetHeight());
    }

    game1.Put(0, 0).SetType(ObjectType::BABA).SetText(true);
    game1.Put(1, 0).SetType(ObjectType::IS);
    game1.Put(2, 0).SetType(ObjectType::FLAG).SetText(true);

    game1.Put(4, 0).SetType(ObjectType::FLAG);

    const auto toIndex = [](std::size_t x, std::size_t y,
                                         std::size_t c) {
        return (c * 100) + (y * 10) + x;
    };


    game1.Update();
    tensor = Preprocess::StateToTensor(game1);

    EXPECT_FLOAT_EQ(tensor[toIndex(0, 0, 0)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(1, 0, 2)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(2, 0, 1)], 1.f);

    EXPECT_FLOAT_EQ(tensor[toIndex(0, 0, 5)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(1, 0, 5)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(2, 0, 5)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(4, 0, 5)], 0.f);

    EXPECT_FLOAT_EQ(tensor[toIndex(0, 0, 6)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(1, 0, 6)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(2, 0, 6)], 1.f);
    EXPECT_FLOAT_EQ(tensor[toIndex(4, 0, 6)], 0.f);
}
