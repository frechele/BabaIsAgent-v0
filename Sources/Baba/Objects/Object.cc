// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#include <Baba/Objects/Object.h>

namespace Baba
{
Object::Object()
    : type_(ObjectType::INVALID)
{
    // Do nothing
}

Object::Object(ObjectType type)
    : type_(type)
{
    // Do nothing
}

ObjectType Object::GetType() const
{
    return ObjectType::TEXT_EMPTY;
}
}  // namespace Baba
