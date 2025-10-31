#ifndef LIB
#define LIB
#include <string>
#ifdef __cplusplus

extern std::string file_data();
struct Pool {
  std::string d_file_data;
};

extern "C" {
#endif
void setter(Pool *);
#ifdef __cplusplus
}
#endif
#endif // !LIB
