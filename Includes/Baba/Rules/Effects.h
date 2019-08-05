// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_EFFECTS_H
#define BABA_EFFECTS_H

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Game.h>
#include <Baba/Objects/Object.h>
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
    //! Default destructor
    ~Effects() = default;

    static Effects& GetInstance();
    
    //! Emplace effect to effects_
    void EmplaceEffect(EffectType effectType, std::function<void(Game&, Object&, Rule&)> func);

    //! Implement effects of the texts that exist block.
    void ImplementBlockEffects();

    //! Implement effects of the texts that don't exist block.
    void ImplementNonBlockEffects();

    std::map<EffectType, std::function<void(Game&, Object&, Rule&)>> effects_;
};
}  // namespace Baba

#endif  // BABA_EFFECTS_H
