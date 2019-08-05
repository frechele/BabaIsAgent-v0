// Copyright(c) 2019 Hyeonsu Kim

#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>

#include <cassert>

namespace Baba
{
ObjectBuilder::ObjectBuilder()
{
    // Do nothing
}

ObjectBuilder& ObjectBuilder::Init()
{
    object_ = new Object();
    
    return *this;
}

ObjectBuilder& ObjectBuilder::SetObjectType(ObjectType objectType)
{
    object_->type_ = objectType;

    return *this;
}

ObjectBuilder& ObjectBuilder::SetEffectType(EffectType effectType)
{
    object_->effectType_ = effectType;

    return *this;
}

ObjectBuilder& ObjectBuilder::SetEffects(std::vector<EffectType> effects)
{
    for (auto& effect : effects)
    {
        EffectsBitset bitset;
        bitset.set(static_cast<int>(effect));
        object_->enchants_.emplace(-1, bitset);
    }

    return *this;
}

Object* ObjectBuilder::Build() const
{
    assert(object_->type_ == ObjectType::INVALID || object_->effectType_ == EffectType::INVALID);

    return object_;
}
} // namespace Baba
