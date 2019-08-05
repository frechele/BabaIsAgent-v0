// Copyright(c) 2019 Junyeong Park

#ifndef BABA_RULES_H
#define BABA_RULES_H

#include <map>
#include <vector>

namespace Baba
{
//!
//! \brief Game rule manager
//!
class GameRules final
{
 private:
    //! Constructor
    GameRules();

 public:
    //! Default destructor
    ~GameRules() = default;

    GameRules& GetInstance();
};
}  // namespace Baba

#endif  // BABA_RULES_H
