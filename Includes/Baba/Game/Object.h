// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_H
#define BABA_OBJECT_H

#include <Baba/Enums/ObjectType.h>

#include <vector>

namespace Baba
{
//!
//! \brief Object that conists level
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

    int GetID() const;

    bool IsText() const;
    Object& SetText(bool value);
    
    Object& SetType(ObjectType type);
    ObjectType GetType() const;

    Object& AddProperty(PropertyType type);
    void RemoveProperty(PropertyType type);
    bool HasProperty(PropertyType type) const;

    void Destroy();
    bool IsDestroyed() const;

    bool operator==(const Object& other) const;
    bool operator!=(const Object& other) const;

 private:
    int objectID_;
    std::vector<PropertyType> properties_;
    ObjectType type_ = ObjectType::INVALID;
    bool isText_ = false;

    bool isDestroyed_ = false;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
