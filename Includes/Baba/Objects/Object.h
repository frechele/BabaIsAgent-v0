// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_H
#define BABA_OBJECT_H

#include <Baba/Enums/ObjectType.h>

#include <vector>

namespace Baba
{
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

    //! Constructor with ObjectType
    Object(ObjectType type);

    //! Default destructor
    virtual ~Object() = default;

    //! Return entity type
    //! \return returned entity type
    virtual ObjectType GetType() const = 0;

 private:
    ObjectType type_;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
