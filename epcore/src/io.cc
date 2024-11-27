#include <cassert>
#include <iostream>
#include "io.hh"

#define TB_IMPL 1
#include "extern/termbox2.h"



unsigned io_event::get_value()  {
  return this->value;
}


epIO::epIO() {
  // std::cout << smcup << std::flush;
  tb_init();
  tb_set_cursor(0, 0);
  // assert(err && "Failed to start termbox2 sesion");
}

epIO::~epIO() {

  tb_shutdown();

  // assert(err && "Ungraceful shutdown of termbox2 sesion");
  // std::cout << rmcup << std::flush;
}





  
// epIO &epIO::operator<<() {
//   TB_RED
//   tb_printf(int x, int y, uintattr_t fg, uintattr_t bg, const char *fmt, ...)
// }


epIO &epIO::operator>>(io_event &event) {
  tb_event e;
  tb_poll_event(&e);
  
  if (e.ch) {
    event.value = e.ch;
  } else {
    event.value = ch_max + e.key;
  }

  return *this;
}

io_event epIO::poll_event() {
  io_event e;
  *this >> e;
  return e;
}



int str_center(const std::string &s) { return s.length() / 2; }
