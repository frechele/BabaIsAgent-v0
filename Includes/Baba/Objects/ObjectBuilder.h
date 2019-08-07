// Copyright(c) 2019 Hyeonsu Kim

#ifndef BABA_OBJECT_BUILDER_H
#define BABA_OBJECT_BUILDER_H

#include <Baba/Enums/ObjectType.h>
#include <Baba/Objects/Object.h>

#include <bitset>
#include <vector>

namespace Baba
{
//!
//! \brief Object that conists level
//!
class ObjectBuilder
{
 public:
    //! Constructor
    ObjectBuilder();

    //! Default destructor
    ~ObjectBuilder();

    //! Delete copy constructor
    ObjectBuilder(const ObjectBuilder&) = delete;

    //! Delete move constructor
    ObjectBuilder(ObjectBuilder&&) = delete;

    //! Delete copy assignment operator
    ObjectBuilder& operator=(const ObjectBuilder&) = delete;

    //! Delete move assignment operator
    ObjectBuilder& operator=(ObjectBuilder&&) = delete;
    
    //! Init ObjectBuilder class
    //! \return Return own reference.
    ObjectBuilder& Init();

    //! Set ObjectType of Object
    //! \return Return own reference.
    ObjectBuilder& SetObjectType(ObjectType objectType);

    //! Set EffectType of Object
    //! \return Return own reference.
    ObjectBuilder& SetEffectType(EffectType effectType);

    //! Set the applied effects to Object.
    //! \return Return own reference.
    ObjectBuilder& SetEffects(std::vector<EffectType> effects);

    //! Returns a created Object
    //! \return A created Object.
    Object& Build();

 private:
    Object* object_;
    std::vector<Object*> objects_;
};
}  // namespace Baba

#endif  // BABA_OBJECT_BUILDER_H
