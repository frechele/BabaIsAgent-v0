// Copyright(c) 2019 Junyeong Park

#ifndef BABA_ENTITY_H
#define BABA_ENTITY_H

#include <Baba/Enums/EntityType.h>

namespace Baba
{
//!
//! \brief Entity interface that conists level
//!
class Entity
{
 public:
    //! Default destructor
    virtual ~Entity() = default;

    //! Return entity type
    //! \return returned entity type
    virtual EntityType GetType() const = 0;
};
}  // namespace Baba

#endif  // BABA_ENTITY_H
