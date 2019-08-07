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

    Object& SetType(ObjectType type);
    ObjectType GetType() const;

    Object& SetEffectType(EffectType type);
    EffectType GetEffectType() const;

    Object& SetEffect(EffectType effect, int ruleID = -1);
    Object& SetEffects(const std::vector<EffectType>& effects);
    const EffectsBitset GetEffects() const;

    void Destroy();
    bool IsDestroyed() const;

    bool operator==(const Object& other) const;
    bool operator!=(const Object& other) const;

 private:
    std::map<std::size_t, EffectsBitset> enchants_;
    ObjectType type_ = ObjectType::INVALID;
    EffectType effectType_ = EffectType::INVALID;

    bool isDestroyed_ = false;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
