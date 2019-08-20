// Copyright(C) 2019 Junyeong Park

#include <pybind11/stl.h>

#include <pyBaba/Agent.h>

#include <Baba/Agent/Agent.h>
#include <Baba/Agent/Preprocess.h>
#include <Baba/Agent/RandomAgent.h>

namespace py = pybind11;
using namespace Baba;

void buildPreprocess(py::module& m)
{
    py::class_<Preprocess>(m, "Preprocess")
        .def_static("StateToTensor", &Preprocess::StateToTensor)
        .def_readonly_static("TENSOR_DIM", &Preprocess::TENSOR_DIM);
}

void buildAgents(py::module& m)
{
    py::class_<Agent> agent(m, "Agent");

    py::class_<RandomAgent>(m, "RandomAgent", agent)
        .def(py::init<>())
        .def("GetAction", &RandomAgent::GetAction);
}
