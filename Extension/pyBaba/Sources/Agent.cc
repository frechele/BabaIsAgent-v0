// Copyright(C) 2019 Junyeong Park

#include <pyBaba/Agent.h>

#include <Baba/Agent/Agent.h>
#include <Baba/Agent/RandomAgent.h>

namespace py = pybind11;
using namespace Baba;

void buildAgents(py::module& m)
{
    py::class_<Agent> agent(m, "Agent");

    py::class_<RandomAgent>(m, "RandomAgent", agent)
        .def(py::init<>())
        .def("GetAction", &RandomAgent::GetAction);
}
