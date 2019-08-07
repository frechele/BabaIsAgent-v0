// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_RULE_H
#define BABA_RULE_H

#include <Baba/Objects/Object.h>

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
    Rule(ObjectType target, VerbType verb, EffectType effect, int ruleID);

    //! Default destructor
    virtual ~Rule() = default;

    //! Returns target object's type
    //! \return Target object's type
    ObjectType GetTarget() const;

    //! Returns object's verb
    //! \return Object's verb
    VerbType GetVerb() const;
    
    //! Returns effect's type
    //! \return Effect's type
    EffectType GetEffect() const;

    //! Returns Rule's id
    //! \return Rule's id
    int GetRuleID() const;

 private:
    ObjectType target;
    VerbType verb;
    EffectType effect;

    int ruleID;
};
}  // namespace Baba

#endif  // BABA_RULE_H
