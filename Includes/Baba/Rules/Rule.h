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
    Rule(ObjectType target, std::string_view verb, EffectType effect, int ruleID);

    //! Default destructor
    virtual ~Rule() = default;

    ObjectType target;
    std::string verb;
    EffectType effect;

    int ruleID;
};
}  // namespace Baba

#endif  // BABA_RULE_H
