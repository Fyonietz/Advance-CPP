#ifndef LIB
#define LIB
#include <string>
#include <unordered_map>
#ifdef __cplusplus

extern std::string file_data();
struct Pool {
  std::string d_file_data;
  std::unordered_map<std::string, std::string> d_u_m;
};

extern "C" {
#endif
void setter(Pool *);
#ifdef __cplusplus
}
#endif
#endif // !LIB
