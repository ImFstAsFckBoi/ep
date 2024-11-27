#include "buffer.hh"
#include "extern/termbox2.h"
#include <fstream>

int Cursor::up(int n) {
  this->Y = std::max(this->Y - n, 0);
  return Y;
}
int Cursor::left(int n) {
  X = std::max(this->X - n, 0);
  return X;
}
int Cursor::right(int n) {
  X += n;
  return X;
}
int Cursor::down(int n) {
  Y += n;
  return Y;
}
void Cursor::set(int x, int y) {
  this->X = x;
  this->Y = y;
}

Buffer::Buffer(std::string const &init_content)
    : lines{init_content, init_content, init_content}, cursor{0, 0} {};

void Buffer::draw(int x, int y, int lines, int line_width) const {
  int c = y;
  int stop = y + lines;

  for (const std::string &l : this->lines) {
    tb_printf(0, c, TB_WHITE, TB_DEFAULT, "%-*s", line_width, l.c_str());
    if (c++ == stop) // lol
      break;
  }
}

void Buffer::insert_at_point(std::string const &str) {
  this->lines.at(cursor.Y).insert(cursor.X, str);
}

Cursor &Buffer::get_cursor() { return this->cursor; }

void load_file(std::string const &path, Buffer &buffer) {
  std::ifstream file{path};
  std::string line;
  while (std::getline(file, line)) {
    buffer.lines.push_back(line);
  }
}
