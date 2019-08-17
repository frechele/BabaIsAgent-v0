// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Game/Object.h>

#include <algorithm>
#include <stdexcept>

namespace Baba
{
Object::Object()
{
    static int ObjectID = 0;

    objectID_ = ObjectID++;
}

int Object::GetID() const
{
    return objectID_;
}

bool Object::IsText() const
{
    return isText_;
}

Object& Object::SetText(bool val)
{
    if ((IsTextType(type_) || IsVerbType(type_) || IsPropertyType(type_)) && !val)
    {
        throw std::logic_error("Cannot set to not text");
    }

    isText_ = val;
    AddProperty(PropertyType::WORD);
    AddProperty(PropertyType::PUSH);

    return *this;
}

Object& Object::SetType(ObjectType type)
{
    if (type == ObjectType::INVALID)
    {
        throw std::runtime_error("Invalid object type");
    }

    if (IsTextType(type) || IsVerbType(type) || IsPropertyType(type))
    {
        isText_ = true;
        AddProperty(PropertyType::WORD);
        AddProperty(PropertyType::PUSH);
    }

    type_ = type;

    return *this;
}

ObjectType Object::GetType() const
{
    return type_;
}

Object& Object::AddProperty(PropertyType type)
{
    properties_.emplace(type);

    return *this;
}

void Object::RemoveProperty(PropertyType type)
{
    auto it = std::find(properties_.begin(), properties_.end(), type);

    if (it != properties_.end())
    {
        properties_.erase(it);
    }
}

bool Object::HasProperty(PropertyType type) const
{
    return std::find(properties_.begin(), properties_.end(), type) !=
           properties_.end();
}

void Object::Destroy()
{
    if (isDestroyed_)
    {
        throw std::runtime_error("Already destroyed object");
    }

    isDestroyed_ = true;
}

bool Object::IsDestroyed() const
{
    return isDestroyed_;
}

bool Object::operator==(const Object& other) const
{
    return (objectID_ == other.objectID_);
}

bool Object::operator!=(const Object& other) const
{
    return !(*this == other);
}
}  // namespace Baba
