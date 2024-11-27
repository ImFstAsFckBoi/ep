#pragma once
#include <string>
#include <vector>


struct Cursor {
  int X, Y;
  int up(int n);
  int left(int n);
  int right(int n);
  int down(int n);
  void set(int x, int y);
};


struct Buffer {
  std::vector<std::string> lines;
  Cursor cursor;

  Buffer(std::string const &init_content = "~scratch buffer~");
  virtual ~Buffer() = default;

  void insert_at_point(std::string const &str);
  Cursor &get_cursor();

  void draw(int x, int y, int lines, int line_width) const;
};

void load_file(std::string const &path, Buffer &buffer);
