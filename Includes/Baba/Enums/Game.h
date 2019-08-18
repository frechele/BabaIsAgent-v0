// Copyright(c) 2019 Hyeonsu Kim

#ifndef BABA_ENUMS_GAME_H
#define BABA_ENUMS_GAME_H

namespace Baba
{
//!
//! \brief Enumerator of game results
//!
enum class GameResult
{
    INVALID,
    WIN,
    DEFEAT,
    COUNT,
};
}  // namespace Baba

//!
//! \brief Enumerator of direction
//!
enum class Direction
{
    INVALID,
    UP,
    DOWN,
    LEFT,
    RIGHT,
};

#endif  // BABA_ENUMS_GAME_H