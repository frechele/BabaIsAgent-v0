// Copyright(c) 2019 Hyeonsu Kim

#ifndef BABA_ENUMS_GAME_H
#define BABA_ENUMS_GAME_H

namespace Baba
{
//!
//! \brief Enumerator of game steps
//!
enum class GameStep
{
    INVALID,
    START_BEGIN,
    START_LOAD_MAP,
    MAIN_INIT,
    MAIN_PARSE_RULES,
    MAIN_APPLY_RULES,
    MAIN_DETERMINE_RESULT,
    MAIN_WAIT_ACTION,
    MAIN_DO_ACTION,
    END_WIN,
    END_DEFEAT,
    COUNT,
};

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