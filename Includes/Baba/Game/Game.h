// Copyright(c) 2019 Junyeong Park

#ifndef BABA_GAME_H
#define BABA_GAME_H

#include <Baba/Game/Object.h>
#include <Baba/Rules/Rules.h>

#include <vector>

namespace Baba
{
//!
//! \brief Class that represents game level
//!
class Game final
{
 public:
    //! Constructor with level shape
    Game(std::size_t width, std::size_t height);

    //! Default destructor
    ~Game();

    //! Delete copy constructor
    Game(const Game&) = delete;

    //! Delete move constructor
    Game(Game&&) = delete;

    //! Delete copy assignment operator
    Game& operator=(const Game&) = delete;

    //! Delete move assignment operator
    Game& operator=(Game&&) = delete;

    //! Return level's width
    //! \return Returned level's width
    std::size_t GetWidth() const;

    //! Return level's height
    //! \return Returned level's height
    std::size_t GetHeight() const;

    //! Get objects in that position
    //! \param x x position
    //! \param y y position
    //! \return Object in that position vector
    const Object::Arr& At(std::size_t x, std::size_t y) const;
    
    //! Put object in that position
    //! \param x x position
    //! \param y y position
    //! \return Created object
    Object& Put(std::size_t x, std::size_t y);

    //! Destory object
    //! \param object Object will be destroyed
    void DestroyObject(Object& object);

    //! Find objects by type
    //! \param Object's type
    //! \return Objects having the same \p type
    Object::Arr FindObjectsByType(ObjectType type) const;
    
    //! Find objects by Property
    //! \param property Object's property
    //! \return Objects having the same \p property
    Object::Arr FindObjectsByProperty(EffectType property) const;

    //! Find objects by Position of target
    //! \param target Object to provide position
    //! \return Objects havaing the same position as target
    Object::Arr FindObjectsByPosition(const Object& target) const;

    //! Apply all rules 
    void ApplyRules();

    Rules gameRules;
 private:
    std::size_t width_, height_;
    Object::Arr objects_;
    std::vector<Object::Arr> map_;
};
}  // namespace Baba

#endif  // BABA_GAME_H
