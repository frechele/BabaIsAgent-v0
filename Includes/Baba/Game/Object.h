// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_H
#define BABA_OBJECT_H

#include<Baba/Enums/Game.h>
#include <Baba/Enums/ObjectType.h>

#include <set>

namespace Baba
{
//!
//! \brief Object that consists level
//!
class Object
{
 public:
    //! Pointer vector wrapper
    using Arr = std::vector<Object*>;

 public:
    //! Constructor
    Object();

    //! Default destructor
    ~Object() = default;

    //! Delete copy constructor
    Object(const Object&) = delete;

    //! Delete move constructor
    Object(Object&&) = delete;

    //! Delete copy assignment operator
    Object& operator=(const Object&) = delete;

    //! Delete move assignment operator
    Object& operator=(Object&&) = delete;

    //! Get object id
    //! \return ID of object
    int GetID() const;

    //! Check object is text
    //! \return Whether object is text
    bool IsText() const;
    //! Set object text status
    //! \param value Whether object is text
    //! \return This object
    Object& SetText(bool value);
    
    //! Set object type
    //! \param type Object type
    //! \return This object
    Object& SetType(ObjectType type);
    //! Get object type
    //! \return Object type
    ObjectType GetType() const;

    //! Add property to object
    //! \param type Property type to add
    //! \return This object
    Object& AddProperty(PropertyType type);
    //! Remove property from object
    //! \param type Property type to remove
    void RemoveProperty(PropertyType type);
    //! Check object has property
    //! \param type Property type
    //! \return Whether object has property type
    bool HasProperty(PropertyType type) const;

	void SetDirection(Direction dir);
	Direction GetDirection() const;

    //! Destroy object
    void Destroy();
    //! Check object is destroyed
    //! \return Whether object is destroyed
    bool IsDestroyed() const;

    bool operator==(const Object& other) const;
    bool operator!=(const Object& other) const;

 private:
    int objectID_;
    std::set<PropertyType> properties_;
    ObjectType type_ = ObjectType::INVALID;
    Direction dir_ = Direction::INVALID;
    bool isText_ = false;

    bool isDestroyed_ = false;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
