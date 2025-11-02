#include "libs.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> map_func() {
  std::unordered_map<std::string, std::string> u_m = {{"Hellow", "World"},
                                                      {"Undordered", "Map"}};
  return std::move(u_m);
};
std::string file_data() {
  std::string file_named = "libs/dynamic.txt";
  std::ifstream f(file_named);

  if (!f.is_open()) {
    std::cerr << "Error Opened: " << file_named << std::endl;
    return "";
  }

  std::stringstream ss;
  ss << f.rdbuf();
  return std::move(ss.str());
}

void setter(Pool *p) {
  if (p == nullptr) {
    std::cerr << "Pool Is NULL" << std::endl;
    return;
  }
  p->d_file_data = std::move(file_data());
  p->d_u_m = std::move(map_func());
}
