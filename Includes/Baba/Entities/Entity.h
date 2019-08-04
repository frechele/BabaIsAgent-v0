// Copyright(c) 2019 Junyeong Park

#ifndef BABA_ENTITY_H
#define BABA_ENTITY_H

#include <Baba/Enums/EntityType.h>

namespace Baba
{
//!
//! \brief Entity that conists level
//!
class Entity
{
 public:
    //! Constructor
    Entity();

    //! Constructor with EntityType
    Entity(EntityType type);

    //! Default destructor
    virtual ~Entity() = default;

    //! Return entity type
    //! \return returned entity type
    virtual EntityType GetType() const = 0;

 private:
    EntityType type_;
};
}  // namespace Baba

#endif  // BABA_ENTITY_H
