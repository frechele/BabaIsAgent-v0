// Copyright(c) 2019 Hyeonsu Kim

#ifndef BABA_UTILS_H
#define BABA_UTILS_H

#include <Baba/Enums/ObjectType.h>
#include <Baba/Game/Object.h>

namespace Baba::Utils
{
//! Check Word
bool ValidateWord(const Object& object);

//! Check Word
bool ValidateWord(const Object& object, const std::vector<WordClass>& classes);
}  // namespace Baba::Utils

#endif  // BABA_UTILS_H
