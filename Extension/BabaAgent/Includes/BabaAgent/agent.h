// Copyright(C) Junyeong Park

#ifndef BABAAGENT_AGENT_H
#define BABAAGENT_AGENT_H

#include <Baba/Agent/Agent.h>

namespace Baba
{
class RLAgent : public Agent
{
 public:
    virtual ~RLAgent() = default;

    Baba::Action GetAction(const Baba::Game& state) override;
};
}  // namespace Baba

#endif  // BABAAGENT_AGENT_H
