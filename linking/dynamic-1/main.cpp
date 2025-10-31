// Main .cpp
#include "libs.hpp"
#include <dlfcn.h>
#include <iostream>
#include <ostream>

typedef void (*setter_t)(Pool *);
//
int loader() {
  void *handle = dlopen("./libdynamic.so", RTLD_LAZY);
  if (!handle) {
    std::cerr << "Failed To Open library" << std::endl;
    return 1;
  }
  dlerror();

  setter_t setter_func = (setter_t)dlsym(handle, "setter");
  const char *error = dlerror();
  if (error) {
    std::cerr << "Error Loading Function" << error << std::endl;
    dlclose(handle);
    return 1;
  }
  std::cout << "From Library" << std::endl;
  Pool p;
  setter_func(&p);
  std::cout << "From file_data(): " << p.d_file_data << std::endl;
  dlclose(handle);
  return 0;
}

int main() {
  loader();
  std::cout << "Work Lee" << std::endl;
  return 0;
}
