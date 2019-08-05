// Copyright(c) 2019 Junyeong Park

#include <Baba/Game/Game.h>

namespace Baba
{
Game::Game(std::size_t width, std::size_t height)
    : width_(width), height_(height), map_(width * height)
{
    // Do nothing
}

std::size_t Game::GetWidth() const
{
    return width_;
}

std::size_t Game::GetHeight() const
{
    return height_;
}

const Object::Arr& Game::At(std::size_t x, std::size_t y) const
{
    return map_[x + y * width_];
}

Object::Arr Game::FindObjectsByType(ObjectType type) const
{
    Object::Arr result;

    for (auto& objs : map_)
    {
        for (Object* obj : objs)
        {
            if (obj->GetType() == type)
            {
                result.emplace_back(obj);
            }
        }
    }

    return result;
}
}  // namespace Baba
