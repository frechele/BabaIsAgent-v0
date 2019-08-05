// Copyright(c) 2019 Junyeong Park

#ifndef BABA_AGENT_H
#define BABA_AGENT_H

#include <Baba/Enums/Action.h>
#include <Baba/Game/Game.h>

namespace Baba
{
//!
//! \brief Agent interface
//!
class Agent
{
 public:
    //! Default destructor
    virtual ~Agent() = default;

    //! Generate agent's action
    //! \param state Current game state
    //! \return Generated agent's action
    virtual Action GetAction(const Game& state) = 0;
};
}  // namespace Baba

#endif  // BABA_AGENT_H
