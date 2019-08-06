// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_H
#define BABA_OBJECT_H

#include <Baba/Enums/ObjectType.h>

#include <bitset>
#include <map>
#include <vector>

namespace Baba
{
using EffectsBitset = std::bitset<static_cast<std::size_t>(EffectType::COUNT)>;
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

    const EffectsBitset GetEffects() const;

    bool operator==(const Object& other) const;
    bool operator!=(const Object& other) const;

    std::map<std::size_t, EffectsBitset> enchants;
    ObjectType type = ObjectType::INVALID;
    EffectType effectType = EffectType::INVALID;

    bool isDestroyed = false;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
