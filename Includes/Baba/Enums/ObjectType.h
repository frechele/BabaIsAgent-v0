// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_TYPE_H
#define BABA_OBJECT_TYPE_H

#include <cstddef>
#include <string>
#include <vector>

namespace Baba
{
//!
//! \brief Enumerator of object types
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

//!
//! \brief Enumerator of verb types
//!
enum class VerbType
{
    INVALID,
#define X(a) a,
#include "VerbType.def"
#undef X
    COUNT,
};

//!
//! \brief Enumerator of property types
//! 
enum class PropertyType
{
    INVALID,
#define X(a) a,
#include "PropertyType.def"
#undef a
    COUNT,
};

//! Check \p type is object type
//! \param type Object type
//! \return Whether type is object type
constexpr bool IsObjectType(ObjectType type)
{
    return (type > ObjectType::OBJECT_TYPE && type < ObjectType::VERB_TYPE);
}

//! Check \p type is verb type
//! \param type Object type
//! \return Whether type is verb type
constexpr bool IsVerbType(ObjectType type)
{
    return (type > ObjectType::VERB_TYPE && type < ObjectType::TEXT_TYPE);
}

//! Check \p type is text type
//! \param type Object type
//! \return Whether type is text type
constexpr bool IsTextType(ObjectType type)
{
    return (type > ObjectType::TEXT_TYPE && type < ObjectType::PROP_TYPE);
}

//! Check \p type is property type
//! \param type Object tyep
//! \return Whether type is property type
constexpr bool IsPropertyType(ObjectType type)
{
    return (type > ObjectType::PROP_TYPE && type < ObjectType::COUNT);
}

//! Convert object type to property type
//! \param type Object type
//! \return Converted type
constexpr PropertyType ObjectToProperty(ObjectType type)
{
    if (IsPropertyType(type))
    {
        return static_cast<PropertyType>(
            static_cast<std::size_t>(type) -
            static_cast<std::size_t>(ObjectType::PROP_TYPE));
    }
    else
    {
        return PropertyType::INVALID;
    }
}

//! Convert property type toobject tyep
//! \param type Property type
//! \return Converted type
constexpr ObjectType PropertyToObject(PropertyType type)
{
    return (type <= PropertyType::INVALID || type >= PropertyType::COUNT)
               ? ObjectType::INVALID
               : static_cast<ObjectType>(
                     static_cast<std::size_t>(type) +
                     static_cast<std::size_t>(ObjectType::PROP_TYPE));
}
}  // namespace Baba

#endif  // BABA_OBJECT_TYPE_H
