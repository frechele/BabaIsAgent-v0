// Copyright(c) 2019 Junyeong Park, Hyeonsu Kim

#ifndef BABA_OBJECT_H
#define BABA_OBJECT_H

#include <Baba/Enums/ObjectType.h>

#include <bitset>
#include <map>
#include <vector>

namespace Baba
{
struct BlockInfo
{
    ObjectName name = ObjectName::INVALID;
    WordClass wordClass = WordClass::INVALID;
    bool isTextObject = false;
};

using PropertyBitset = std::bitset<static_cast<std::size_t>(ObjectName::COUNT)>;
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
    Object(BlockInfo info);

    //! Default destructor
    ~Object() = default;

    //! Delete copy constructor
    Object(const Object&) = delete;

    //! Delete move constructor
    Object(Object&&) = delete;

    //! Delete copy assignment operator
    Object& operator=(const Object&) = delete;

    //! Delete move assignment operator
    Object& operator=(Object&&) = delete;

    int GetID() const;
    
    Object& SetName(ObjectName name);
    ObjectName GetName() const;
    WordClass GetWordClass() const;
    PropertyBitset GetProperty() const;

    Object& AddEnchant(ObjectName effect, int ruleID);
    void RemoveEnchant(int ruleID);

    void Destroy();
    bool IsDestroyed() const;
    bool IsText() const;

    bool operator==(const Object& other) const;
    bool operator!=(const Object& other) const;

 private:
    int objectID_;
    std::map<std::size_t, PropertyBitset> enchants_;
    BlockInfo info_;

    bool isDestroyed_ = false;
};
}  // namespace Baba

#endif  // BABA_OBJECT_H
