// Copyright(c) 2019 Hyeonsu Kim

#ifndef BABA_ENUMS_GAME_H
#define BABA_ENUMS_GAME_H

namespace Baba
{
//!
//! \brief Game steps
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

enum class GameResult
{
    INVALID,
    WIN,
    DEFEAT,
    COUNT,
};
}  // namespace Baba

#endif  // BABA_ENUMS_GAME_H