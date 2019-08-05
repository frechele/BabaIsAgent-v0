// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_RULES_H
#define BABA_RULES_H

#include <Baba/Rules/Rule.h>

#include <list>
#include <string_view>

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

    //! Add base rule.
    //! \param target target's type.
    //! \param verb verb's type.
    //! \param effect effect's type.
    //! \return id of rule.
    const int AddBaseRule(ObjectType target, std::string_view verb, EffectType effect);

    //! Delete rule.
    //! \param ruleID id of rule to delete.
    void DeleteRule(const int& ruleID);

    int ruleCount = 0;
    std::list<Rule> rules_;
};
}  // namespace Baba

#endif  // BABA_RULES_H
