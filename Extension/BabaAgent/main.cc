// Copyright(C) 2019 Junyeong Park

#include <pybind11/pybind11.h>

int add(int a, int b)
{
    return a + b;
}

PYBIND11_MODULE(BabaAgent, m)
{
    m.doc() = R"pbdoc(Baba is you reinforcement learning agent)pbdoc";

    m.def("add", &add, "A function which adds two numbers");
}
