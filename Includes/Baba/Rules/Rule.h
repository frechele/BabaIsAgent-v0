// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_RULE_H
#define BABA_RULE_H

#include <Baba/Game/Object.h>

namespace Baba
{
//!
//! \brief Rule that conists level
//!
class Rule
{
 public:
    //! Constructor
    Rule(ObjectType target, ObjectType verb, ObjectType effect);

    //! Default destructor
    virtual ~Rule() = default;

    //! Returns target object's type
    //! \return Target object's type
    ObjectType GetTarget() const;

    //! Returns object's verb
    //! \return Object's verb
    ObjectType GetVerb() const;
    
    //! Returns effect's type
    //! \return Effect's type
    ObjectType GetEffect() const;

    //! Returns Rule's id
    //! \return Rule's id
    std::int64_t GetRuleID() const;

    //! Calculate Rule's id
    //! \param target Rule target
    //! \param verb Rule verb
    //! \param effect Rule effect
    //! \return Rule's id
    static std::int64_t CalcRuleID(ObjectType target, ObjectType verb, ObjectType effect);

    bool operator<(const Rule& other) const;

 private:
    ObjectType target_;
    ObjectType verb_;
    ObjectType effect_;
};
}  // namespace Baba

#endif  // BABA_RULE_H
