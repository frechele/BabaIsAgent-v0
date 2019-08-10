// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_TYPE_H
#define BABA_OBJECT_TYPE_H

#include <cstddef>
#include <string>
#include <vector>

namespace Baba
{
//!
//! \brief Enumerator of entity types
//!
enum class ObjectType
{
    INVALID,
#define X(a) a,
    OBJECT_TYPE,
#include "ObjectType.def"
    VERB_TYPE,
#include "VerbType.def"
    TEXT_TYPE,
#include "TextType.def"
    PROP_TYPE,
#include "PropertyType.def"
#undef X
    COUNT,
};

enum class VerbType
{
    INVALID,
#define X(a) a,
#include "VerbType.def"
#undef X
    COUNT,
};

enum class PropertyType
{
    INVALID,
    DECLARE,
#define X(a) a,
#include "PropertyType.def"
#undef a
    COUNT,
};

constexpr bool IsObjectType(ObjectType type)
{
    return (type > ObjectType::OBJECT_TYPE && type < ObjectType::VERB_TYPE);
}

constexpr bool IsVerbType(ObjectType type)
{
    return (type > ObjectType::VERB_TYPE && type < ObjectType::TEXT_TYPE);
}

constexpr bool IsTextType(ObjectType type)
{
    return (type > ObjectType::TEXT_TYPE && type < ObjectType::PROP_TYPE);
}

constexpr bool IsPropertyType(ObjectType type)
{
    return (type > ObjectType::PROP_TYPE && type < ObjectType::COUNT);
}

constexpr PropertyType ObjectToProperty(ObjectType type)
{
    if (IsPropertyType(type))
    {
        return static_cast<PropertyType>(
            static_cast<std::size_t>(type) -
            static_cast<std::size_t>(ObjectType::PROP_TYPE) - 1u);
    }
    else
    {
        return PropertyType::INVALID;
    }
}

constexpr ObjectType PropertyToObject(PropertyType type)
{
    return static_cast<ObjectType>(
        static_cast<std::size_t>(type) +
        static_cast<std::size_t>(ObjectType::PROP_TYPE) + 1u);
}
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
