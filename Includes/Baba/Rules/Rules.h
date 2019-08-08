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
class Rules final
{
 public:
    //! Defalaut constructor
    Rules() = default;

    //! Default destructor
    ~Rules() = default;

    //! Delete copy constructor
    Rules(const Rules&) = delete;

    //! Delete move constructor
    Rules(Rules&&) = delete;

    //! Delete copy assignment operator
    Rules& operator=(const Rules&) = delete;

    //! Delete move assignment operator
    Rules& operator=(Rules&&) = delete;
    
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
    int AddBaseRule(EffectType target, EffectType verb, EffectType effect);

    //! Delete rule.
    //! \param ruleID id of rule to delete.
    void DeleteRule(int ruleID);

 private:
    int ruleCount_ = 0;
    std::list<Rule> rules_;
};
}  // namespace Baba

#endif  // BABA_RULES_H
