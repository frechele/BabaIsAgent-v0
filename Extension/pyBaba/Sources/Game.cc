// Copyrigh(C) 2019 Junyeong Park

#include <pyBaba/Game.h>

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
        .def("Destroy", &Object::Destroy)
        .def("IsDestroyed", &Object::IsDestroyed);
}

void buildGame(py::module& m)
{
    py::class_<Game>(m, "Game")
        .def(py::init<std::size_t, std::size_t>())
        .def("GetWidth", &Game::GetWidth)
        .def("GetHeight", &Game::GetHeight)
        .def("At", &Game::At)
        .def("Put", &Game::Put)
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
        .def("RemoveRule", &Game::RemoveRule)
        .def("GetRules", &Game::GetRules);
}
