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
 public:
    //! Defalaut constructor
    GameRules() = default;

    //! Default destructor
    ~GameRules() = default;

    //! Returns a list of all rules.
    //! \return A list of all rules.
    const std::list<Rule>& GetAllRules();

    //! Returns count of rules.
    //! \return Count of rules.
    int GetRuleCount() const;

    //! Add base rule.
    //! \param target target's type.
    //! \param verb verb's type.
    //! \param effect effect's type.
    //! \return id of rule.
    int AddBaseRule(ObjectType target, const std::string_view& verb, EffectType effect);

    //! Delete rule.
    //! \param ruleID id of rule to delete.
    void DeleteRule(int ruleID);

 private:
    int ruleCount_ = 0;
    std::list<Rule> rules_;
};
}  // namespace Baba

#endif  // BABA_RULES_H
