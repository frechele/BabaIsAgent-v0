// Copyright(c) 2019 Junyeong Park

#ifndef BABA_GAME_H
#define BABA_GAME_H

#include <Baba/Enums/Action.h>
#include <Baba/Enums/Game.h>
#include <Baba/Game/Object.h>
#include <Baba/Rules/Rule.h>

#include <functional>
#include <vector>
#include <set>

namespace Baba
{
//!
//! \brief Class that represents game level
//!
class Game final
{
 public:
    //! Location tuple wrapper
    using Point = std::tuple<std::size_t, std::size_t>;

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

    //! Returns whether a rule exists in that position.
    //! \param x x position
    //! \param y y position
    //! \return Whether a rule exists in that position.
    bool AtRule(std::size_t x, std::size_t y) const;
    
    //! Put object in that position
    //! \param x x position
    //! \param y y position
    //! \return Created object
    Object& Put(std::size_t x, std::size_t y);

    //! Destory object
    //! \param object Object will be destroyed
    void DestroyObject(Object& object);

    //! Find objects by func
    //! \param func function to classify objects
    //! \param excludeTest Exclude text option
    //! \return Objects that satisfy func
    Object::Arr FindObjects(std::function<bool(const Object&)> func, bool excludeText = false) const;

    //! Find objects by type
    //! \param Object's type
    //! \param excludeTest Exclude text option
    //! \return Objects having the same \p type
    Object::Arr FindObjectsByType(ObjectType type, bool excludeText = false) const;
    
    //! Find objects by Property
    //! \param property Object's property
    //! \param excludeTest Exclude text option
    //! \return Objects having the same \p property
    Object::Arr FindObjectsByProperty(PropertyType property, bool excludeText = false) const;

    //! Find objects by Position of target
    //! \param target Object to provide position
    //! \param excludeTest Exclude text option
    //! \return Objects havaing the same position as target
    Object::Arr FindObjectsByPosition(const Object& target, bool excludeText = false) const;

    //! Filter objects by func
    //! \param objects objects to be filtered
    //! \param func function to classify objects
    //! \return filtered objects
    Object::Arr FilterObjectByFunction(const Object::Arr& objects,
                                       std::function<bool(const Object&)> func) const;

    //! Return target's position
    //! \param target target object
    //! \return position of target
    const Point GetPositionByObject(const Object& target) const;

    //! Check position is valid
    //! \param x x position
    //! \param y y position
    //! \return Whether position is valid
    bool ValidatePosition(std::size_t x, std::size_t y) const;

    //! Update game
    //! \param action Player's action
    void Update(Action action = Action::STAY);

    //! Get game result;
    //! \return GameResult
    GameResult GetGameResult() const;

    //! Add rule
    //! \param target Target of rule
    //! \param verb Verb of rule
    //! \param effect Effect of rule
    //! \return ID of added rule
    std::int64_t AddRule(ObjectType target, ObjectType verb, ObjectType effect);
    
    //! Add base rule
    //! \param target Target of rule
    //! \param verb Verb of rule
    //! \param effect Effect of rule
    //! \return ID of added rule
    std::int64_t AddBaseRule(ObjectType target, ObjectType verb, ObjectType effect);

    //! Remove rule
    //! \param id ID of rule to remove
    void RemoveRule(std::int64_t id);

    //! Tie affected objects as the object move
    //! \param pusher Object to be center of movement
    //! \param dir Direction of movement
    //! \return Tied objects
    Object::Arr TieStuckMoveableObjects(Object& pusher, Direction dir) const;

    //! Move objects without any condition check.
    //! \param objects Objects
    //! \param dir Direction of movement
    void MoveObjects(const Object::Arr& objects, Direction dir);

    //! Get set of rules
    //! \return Set of rules
    const std::set<Rule>& GetRules() const;

    //! Get nowAction_
    //! \return nowAction_
    Action GetNowAction() const;

 private:
    void parseRules();
    void applyRules();
    void applyRules(std::set<Rule>& r, bool doFunc = true);
    void determineResult();
    Point dir2Vec(Direction dir) const;

    std::size_t pt2idx(std::size_t x, std::size_t y) const;

 private:
    std::size_t width_, height_;
    Object::Arr objects_;
    std::vector<Object::Arr> map_;

    std::set<Rule> rules_;
    std::set<Rule> baseRules_;
    std::vector<bool> ruleMap_;
    
    Action nowAction_ = Action::STAY;
    GameResult gameResult_ = GameResult::INVALID;
};
}  // namespace Baba

#endif  // BABA_GAME_H
