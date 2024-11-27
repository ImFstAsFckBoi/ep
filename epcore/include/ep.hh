#pragma once
#include "buffer.hh"
#include "io.hh"
#include "pybind11/pytypes.h"
#include <array>

struct ep {
  epIO io;
  Buffer *buffer;
  std::array<pybind11::object, 200> cmd_vec;


  ep();
  ~ep();

  void draw();
  void set_buffer();
  Buffer &current_buffer();
  epIO &get_io();
};