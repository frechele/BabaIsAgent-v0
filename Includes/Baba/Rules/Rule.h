// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_RULE_H
#define BABA_RULE_H

#include <Baba/Game/Object.h>

#include <string>
#include <string_view>

namespace Baba
{
//!
//! \brief Rule that conists level
//!
class Rule
{
 public:
    //! Constructor
    Rule(Object& target, Object& verb, Object& effect, int ruleID);

    //! Default destructor
    virtual ~Rule() = default;

    //! Returns target object's type
    //! \return Target object's type
    Object& GetTarget() const;

    //! Returns object's verb
    //! \return Object's verb
    Object& GetVerb() const;
    
    //! Returns effect's type
    //! \return Effect's type
    Object& GetEffect() const;

    //! Returns Rule's id
    //! \return Rule's id
    int GetRuleID() const;

 private:
    Object* target_;
    Object* verb_;
    Object* effect_;

    int ruleID_;
};
}  // namespace Baba

#endif  // BABA_RULE_H
