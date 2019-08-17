// Copyright(C) 2019 Junyeong Park

#ifndef PYBABA_ENUMS_H
#define PYBABA_ENUMS_H

#include <pybind11/pybind11.h>

void buildActionEnum(pybind11::module& m);
void buildGameEnum(pybind11::module& m);
void buildObjectTypeEnum(pybind11::module& m);
void buildVerbTypeEnum(pybind11::module& m);
void buildPropertyTypeEnum(pybind11::module& m);
void buildTypeUtilities(pybind11::module& m);

#endif  // PYBABA_ENUMS_H
