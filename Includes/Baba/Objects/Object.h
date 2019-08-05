// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_H
#define BABA_OBJECT_H

#include <Baba/Enums/ObjectType.h>

namespace Baba
{
//!
//! \brief Object that conists level
//!
class Object
{
 public:
    //! Constructor
    Object();

    //! Default destructor
    ~Object() = default;

    std::string name_;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
