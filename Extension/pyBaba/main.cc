// Copyright(C) 2019 Junyeong Park

#include <pyBaba/Enums.h>
#include <pyBaba/Agent.h>
#include <pyBaba/Game.h>

PYBIND11_MODULE(pyBaba, m)
{
    m.doc() = R"pbdoc(Baba is you reinforcement learning agent)pbdoc";

    buildActionEnum(m);
    buildGameEnum(m);
    buildObjectTypeEnum(m);
    buildVerbTypeEnum(m);
    buildPropertyTypeEnum(m);
    buildTypeUtilities(m);

    buildPreprocess(m);
    buildAgents(m);
    buildObject(m);
    buildRule(m);
    buildGame(m);
}
