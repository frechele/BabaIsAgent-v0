// Copyright(C) 2019 Junyeong Park

#ifndef PYBABA_GAME_H
#define PYBABA_GAME_H

#include <pybind11/pybind11.h>

void buildObject(pybind11::module& m);
void buildRule(pybind11::module& m);
void buildGame(pybind11::module& m);

#endif  // PYBABA_GAME_H
