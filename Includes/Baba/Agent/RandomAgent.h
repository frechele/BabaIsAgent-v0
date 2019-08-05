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
    virtual Action GetAction() override;
};
}  // namespace Baba

#endif  // BABA_RANDOM_AGENT_H
