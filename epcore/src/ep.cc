#include "buffer.hh"
#include "io.hh"
#include "ep.hh"
#include "extern/termbox2.h"

#include <cstddef>
#include <string>

ep::ep() : io{}, buffer{new Buffer()}, cmd_vec{} {}

ep::~ep() { delete buffer; }

size_t counter;

void ep::draw() {
  int x = tb_width(), y = tb_height();
  this->buffer->draw(0, 0, y - 2, x);
  tb_printf(0, y - 2, TB_BLACK, TB_WHITE,
            "  ep/v0.1.0  drawcycles=%d COL=%d ROW=%d%-*s", counter++,
            this->buffer->cursor.Y, this->buffer->cursor.X, x, " ");
  tb_set_cursor(this->buffer->cursor.X, this->buffer->cursor.Y);
  tb_present();
}

void ep::set_buffer() {
  this->buffer->lines.clear();
  load_file("test.txt", *this->buffer);
}

Buffer &ep::current_buffer() {
  return *this->buffer;
}

epIO &ep::get_io() {
  return this->io;
}