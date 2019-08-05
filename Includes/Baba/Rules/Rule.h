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
    Rule(std::string_view target, std::string_view verb, std::string_view effect, int ruleID);

    //! Default destructor
    virtual ~Rule() = default;

    std::string target_;
    std::string effect_;
    std::string verb_;

    int ruleID_;
};
}  // namespace Baba

#endif  // BABA_RULE_H
