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
    
    //! Returns count of all rules.
    //! \return Count of all rules.
    std::size_t GetRuleCount() const;

    //! Returns a list of all rules.
    //! \return A list of all rules.
    const std::list<Rule>& GetAllRules();

    //! Add base rule.
    //! \param target target's type.
    //! \param verb verb's type.
    //! \param effect effect's type.
    //! \return id of rule.
    std::int64_t AddBaseRule(ObjectType target, ObjectType verb, ObjectType effect);

    //! Delete rule.
    //! \param ruleID id of rule to delete.
    void DeleteRule(std::int64_t ruleID);

 private:
    std::list<Rule> rules_;
};
}  // namespace Baba

#endif  // BABA_RULES_H
