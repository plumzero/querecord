
#include <cxxabi.h>
#include <typeinfo>
#include <string>
#include <stdlib.h>
#include <iostream>

static inline std::string demangle(const std::string &name) {
  int status = 0;
  char *p = abi::__cxa_demangle(name.c_str(), 0, 0, &status);
  std::string ret(p);
  free(p);
  return ret;
}

template <class T>
std::string readable_typename() {
  return demangle(typeid(T).name());
}

template <>
inline std::string readable_typename<std::string>() {
  return "string";
}

int main()
{
  std::cout << readable_typename<int>() << std::endl;
  std::cout << readable_typename<double>() << std::endl;
  std::cout << readable_typename<std::string>() << std::endl;

  return 0;
}