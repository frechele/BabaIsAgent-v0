// Copyright(c) 2019 Hyeonsu Kim

#ifndef BABA_UTILS_H
#define BABA_UTILS_H

#include <Baba/Enums/ObjectType.h>

namespace Baba::Utils
{

//! Cast EffectType to ObjectType
//! \param effectType EffectType
//! \return ObjectType
ObjectType EffectToObject(EffectType effectType);
}  // namespace Baba::Utils

#endif  // BABA_UTILS_H
