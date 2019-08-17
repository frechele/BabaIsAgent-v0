// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_EFFECTS_H
#define BABA_EFFECTS_H

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Game/Object.h>
#include <Baba/Rules/Rule.h>

#include <functional>
#include <map>

namespace Baba
{
//!
//! \brief Game effect manager
//!
class Effects
{
 private:
    //! Constructor
    Effects();

 public:
    using EffectFunc = std::function<void(Game&, Object&, const Rule&)>;

 public:
    //! Default destructor
    ~Effects() = default;

    //! Delete copy constructor
    Effects(const Effects&) = delete;

    //! Delete move constructor
    Effects(Effects&&) = delete;

    //! Delete copy assignment operator
    Effects& operator=(const Effects&) = delete;

    //! Delete move assignment operator
    Effects& operator=(Effects&&) = delete;

    static Effects& GetInstance();

    //! Returns priority of property
    //! \param propertyType PropertyType
    //! \return priority of propertyType 
    std::uint8_t GetPriority(PropertyType propertyType) const;

    //! Implement effects of the texts that exist block.
    void ImplementBlockEffects();

    //! Implement effects of the texts that don't exist block.
    void ImplementNonBlockEffects();

    //! Returns map of properties
    //! \return Map of properties
    const std::map<PropertyType, EffectFunc>& GetEffects() const;

 private:
    void emplace(PropertyType propertyType, EffectFunc func, std::uint8_t priority);

 private:
    std::map<PropertyType, EffectFunc> effects_;
    std::map<PropertyType, std::uint8_t> priorities_;
};
}  // namespace Baba

#endif  // BABA_EFFECTS_H
