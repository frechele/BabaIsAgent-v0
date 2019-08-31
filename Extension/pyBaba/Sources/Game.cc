// Copyrigh(C) 2019 Junyeong Park

#include <pyBaba/Game.h>
#include <pybind11/functional.h>
#include <pybind11/stl.h>

#include <Baba/Game/Game.h>

namespace py = pybind11;
using namespace Baba;

void buildObject(py::module& m)
{
    py::class_<Object>(m, "Object")
        .def(py::init<>())
        .def("GetID", &Object::GetID)
        .def("IsText", &Object::IsText)
        .def("SetText", &Object::SetText)
        .def("SetType", &Object::SetType)
        .def("GetType", &Object::GetType)
        .def("AddProperty", &Object::AddProperty)
        .def("RemoveProperty", &Object::RemoveProperty)
        .def("HasProperty", &Object::HasProperty)
        .def("SetDirection", &Object::SetDirection)
        .def("GetDirection", &Object::GetDirection)
        .def("Destroy", &Object::Destroy)
        .def("IsDestroyed", &Object::IsDestroyed);
}

void buildRule(py::module& m)
{
    py::class_<Rule>(m, "Rule")
        .def(py::init<ObjectType, ObjectType, ObjectType>())
        .def("GetTarget", &Rule::GetTarget)
        .def("GetVerb", &Rule::GetVerb)
        .def("GetEffect", &Rule::GetEffect)
        .def("GetRuleID", &Rule::GetRuleID)
        .def_static("CalculateRuleID", &Rule::CalcRuleID);
}

void buildGame(py::module& m)
{
    py::class_<Game>(m, "Game")
        .def(py::init<std::size_t, std::size_t>())
        .def("GetWidth", &Game::GetWidth)
        .def("GetHeight", &Game::GetHeight)
        .def("At", &Game::At, py::return_value_policy::reference)
        .def("Put", &Game::Put, py::return_value_policy::reference)
        .def("DestroyObject", &Game::DestroyObject)
        .def("FindObjects", &Game::FindObjects)
        .def("FindObjectsByType", &Game::FindObjectsByType)
        .def("FindObjectsByProperty", &Game::FindObjectsByProperty)
        .def("FindObjectsByPosition", &Game::FindObjectsByPosition)
        .def("FilterObjectsByFunction", &Game::FilterObjectByFunction)
        .def("GetPositionByObject", &Game::GetPositionByObject)
        .def("ValidatePosition", &Game::ValidatePosition)
        .def("Update", &Game::Update)
        .def("GetGameResult", &Game::GetGameResult)
        .def("AddRule", &Game::AddRule)
        .def("AddBaseRule", &Game::AddBaseRule)
        .def("RemoveRule", &Game::RemoveRule)
        .def("TieStuckMoveableObjects", &Game::TieStuckMoveableObjects)
        .def("MoveObjects", &Game::MoveObjects)
        .def("GetRules", &Game::GetRules)
        .def("GetNowAction", &Game::GetNowAction);
}
