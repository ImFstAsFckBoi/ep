#pragma once
#include <string>


struct io_event {
  unsigned value;

  unsigned get_value();
};

constexpr int ch_max = 127;


struct epIO {
  epIO();
  ~epIO();

  epIO &operator<<(std::string out);
  epIO &operator>>(io_event &event);
  
  io_event poll_event();
};



int str_center(const std::string &s);
