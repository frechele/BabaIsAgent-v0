// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Game/Object.h>

#include <algorithm>
#include <stdexcept>

namespace Baba
{
Object::Object() : Object(BlockInfo())
{
    // Do nothing
}

Object::Object(BlockInfo info) : info_(info)
{
    static int ObjectID = 0;

    objectID_ = ObjectID++;
}

Object& Object::SetName(ObjectName name)
{
    if (name == ObjectName::INVALID)
    {
        throw std::runtime_error("Invalid object name");
    }

    info_.name = name;
    return *this;
}

int Object::GetID() const
{
    return objectID_;
}

ObjectName Object::GetName() const
{
    return info_.name;
}

WordClass Object::GetWordClass() const
{
    return info_.wordClass;
}

PropertyBitset Object::GetProperty() const
{
    PropertyBitset result;

    for (const auto& enchant : enchants_)
    {
        result |= enchant.second;
    }

    return result;
}

Object& Object::AddEnchant(ObjectName effect, int ruleID)
{
    PropertyBitset bitset;
    bitset.set(static_cast<int>(effect));
    enchants_.emplace(ruleID, bitset);

    return *this;
}

void Object::RemoveEnchant(int ruleID)
{
    enchants_.erase(ruleID);
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

bool Object::IsText() const
{
    return info_.isTextObject;
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
