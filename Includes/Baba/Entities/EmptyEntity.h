// Copyright(c) 2019 Junyeong Park

#ifndef BABA_EMPTY_ENTITY_H
#define BABA_EMPTY_ENTITY_H

#include <Baba/Entities/Entity.h>

namespace Baba
{
//!
//! \brief Empty block entity
//!
class EmptyBlock final : public Entity
{
 public:
    //! Default destructor
    virtual ~EmptyBlock() = default;

    //! Return entity type
    //! \return returned entity type
    virtual EntityType GetType() const override;
};

//!
//! \brief Empty text entity
//!
class EmptyText final : public Entity
{
 public:
    //! Default destructor
    virtual ~EmptyText() = default;

    //! Return entity type
    //! \return returned entity type
    virtual EntityType GetType() const override;
};
}  // namespace Baba

#endif  // BABA_EMPTY_ENTITY_H
