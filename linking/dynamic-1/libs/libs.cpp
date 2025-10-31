#include "libs.hpp"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>

extern std::string file_data() {
  std::string file_named = "test.txt";
  std::ifstream f(file_named);

  if (!f.is_open()) {
    std::cerr << "Error Opened: " << file_named << std::endl;
return "";
  }

  std::stringstream ss;
  ss << f.rdbuf();
  return ss.str();
}

void setter(Pool *p) {
  p->d_file_data = file_data();
  if (p != nullptr) {
  } else {
    std::cerr << "Error: Pool pointer is null" << std::endl;
  }
}
