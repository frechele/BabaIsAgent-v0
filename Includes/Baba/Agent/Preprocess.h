// Copyright(C) 2019 Junyeong Park

#ifndef BABA_PREPROCESS_H
#define BABA_PREPROCESS_H

#include <Baba/Game/Game.h>

#include <vector>

namespace Baba
{
class Preprocess
{
 public:
    //! Dimension of tensor
    static constexpr int TENSOR_DIM = 7;

    //! Convert state to tensor
    //! \param game Game state
    //! \return Converted tensor
    static std::vector<float> StateToTensor(const Game& game);
};
}  // namespace Baba

#endif  // BABA_PREPROCESS_H
