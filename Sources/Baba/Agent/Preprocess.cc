// Copyright(C) 2019 Junyeong Park

#include <Baba/Agent/Preprocess.h>

#include <map>

namespace
{
std::map<Baba::ObjectType, std::size_t> TensorDimMap = {
    { Baba::ObjectType::BABA, 0 },
    { Baba::ObjectType::FLAG, 1 },
    { Baba::ObjectType::IS, 2 },
    { Baba::ObjectType::WIN, 3 },
    { Baba::ObjectType::YOU, 4 }
};
}

namespace Baba
{
std::vector<float> Preprocess::StateToTensor(const Game& game)
{
    const std::size_t width = game.GetWidth();
    const std::size_t height = game.GetHeight();

    std::vector<float> tensor(Preprocess::TENSOR_DIM * width * height, 0);

    const auto toIndex = [width, height](std::size_t x, std::size_t y,
                                         std::size_t c) {
        return (c * width * height) + (y * width) + x;
    };

    for (std::size_t y = 0; y < height; ++y)
    {
        for (std::size_t x = 0; x < width; ++x)
        {
            auto& objs = game.At(x, y);

            if (objs.size() > 0)
            {
                tensor[toIndex(x, y, TensorDimMap[objs[0]->GetType()])] = 1.f;
                tensor[toIndex(x, y, TENSOR_DIM - 1)] = (objs[0]->IsText() ? 1.f : 0.f);
            }
        }
    }

    return tensor;
}
}  // namespace Baba
