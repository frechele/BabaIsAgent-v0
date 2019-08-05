// Copyright(c) 2019 Junyeong Park

#ifndef BABA_RANDOM_AGENT_H
#define BABA_RANDOM_AGENT_H

#include <Baba/Agent/Agent.h>

namespace Baba
{
//!
//! \brief Agent that plays randomly
//!
class RandomAgent : public Agent
{
 public:
    //! Default destructor
    virtual ~RandomAgent() = default;

    //! Generate agent's action
    //! \param state Current game state
    //! \return Generated agent's action
    Action GetAction(const Game& state) override;
};
}  // namespace Baba

#endif  // BABA_RANDOM_AGENT_H
