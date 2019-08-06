// Copyright(c) 2019 Hyeonsu Kim

#include <Baba/Objects/Object.h>
#include <Baba/Objects/ObjectBuilder.h>

#include <cassert>

namespace Baba
{
ObjectBuilder::ObjectBuilder() : object_(nullptr)
{
    // Do nothing
}

ObjectBuilder::~ObjectBuilder()
{
    if (object_ != nullptr)
    {
        delete object_;
    }

    for (auto& object : objects_)
    {
        delete object;
    }
}

ObjectBuilder& ObjectBuilder::Init()
{
    if (object_ != nullptr)
    {
        delete object_;
    }

    object_ = new Object();
    
    return *this;
}

ObjectBuilder& ObjectBuilder::SetObjectType(ObjectType objectType)
{
    object_->type = objectType;

    return *this;
}

ObjectBuilder& ObjectBuilder::SetEffectType(EffectType effectType)
{
    object_->effectType = effectType;

    return *this;
}

ObjectBuilder& ObjectBuilder::SetEffects(std::vector<EffectType> effects)
{
    for (auto& effect : effects)
    {
        EffectsBitset bitset;
        bitset.set(static_cast<int>(effect));
        object_->enchants.emplace(-1, bitset);
    }

    return *this;
}

Object& ObjectBuilder::Build()
{
    assert(object_->type != ObjectType::INVALID &&
           object_->effectType != EffectType::INVALID);
    
    Object* obj = object_;
    object_ = nullptr;

    return *obj;
}
}  // namespace Baba
