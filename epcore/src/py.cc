#include <pybind11/pybind11.h>

#include "buffer.hh"
#include "ep.hh"
#include "io.hh"


namespace py = pybind11;

PYBIND11_MODULE(epcore, m) {

  /*
      MAIN MODULE epcore
  */
  py::class_<ep>(m, "ep")
      .def(py::init<>())
      .def("current_buffer", &ep::current_buffer, py::return_value_policy::reference)
      .def("io", &ep::get_io, py::return_value_policy::reference)
      .def("draw", &ep::draw);

  py::class_<Buffer>(m, "Buffer")
      .def(py::init<>())
      .def("insert_at_point", &Buffer::insert_at_point)
      .def("get_cursor", &Buffer::get_cursor, py::return_value_policy::reference);

  py::class_<Cursor>(m, "Cursor")
      .def(py::init<>())
      .def("set", &Cursor::set)
      .def("up",&Cursor::up)
      .def("down",&Cursor::down)
      .def("left",&Cursor::left)
      .def("right",&Cursor::right);



  /*
    IO SUBMODULE epcore.io
  */

  py::module_ io = m.def_submodule("io");
  py::class_<io_event> (io, "io_event")
    .def("get_value", &io_event::get_value, py::return_value_policy::copy);

  py::class_<epIO>(io, "epIO")
    .def("poll_event", &epIO::poll_event, py::return_value_policy::move);
}
