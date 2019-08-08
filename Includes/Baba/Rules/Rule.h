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
    Rule(EffectType target, EffectType verb, EffectType effect, int ruleID);

    //! Default destructor
    virtual ~Rule() = default;

    //! Returns target object's type
    //! \return Target object's type
    EffectType GetTarget() const;

    //! Returns object's verb
    //! \return Object's verb
    EffectType GetVerb() const;
    
    //! Returns effect's type
    //! \return Effect's type
    EffectType GetEffect() const;

    //! Returns Rule's id
    //! \return Rule's id
    int GetRuleID() const;

 private:
    EffectType target_;
    EffectType verb_;
    EffectType effect_;

    int ruleID_;
};
}  // namespace Baba

#endif  // BABA_RULE_H
