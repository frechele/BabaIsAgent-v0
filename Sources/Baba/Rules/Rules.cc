// Copyright(c) 2019 Junyeong Park

#include <Baba/Rules/Rules.h>

namespace Baba
{
GameRules& GameRules::GetInstance()
{
    static GameRules instance;
    return instance;
}
}  // namespace Baba
