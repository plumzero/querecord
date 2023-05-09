
#include <stdio.h>
#include <assert.h>
#include <string>
#include <sstream>

template <typename Target, typename Source, bool Same>
class lexical_cast_t {
 public:
  static Target cast(const Source &arg) {
    Target ret;
    std::stringstream ss;
    assert((ss << arg && ss >> ret && ss.eof()));

    return ret;
  }
};

template <typename Target, typename Source>
class lexical_cast_t<Target, Source, true> {
 public:
  static Target cast(const Source &arg) { return arg; }
};

template <typename Source>
class lexical_cast_t<std::string, Source, false> {
 public:
  static std::string cast(const Source &arg) {
    std::ostringstream ss;
    ss << arg;
    return ss.str();
  }
};

template <typename Target>
class lexical_cast_t<Target, std::string, false> {
 public:
  static Target cast(const std::string &arg) {
    Target ret;
    std::istringstream ss(arg);
    assert((ss >> ret && ss.eof()));
    return ret;
  }
};

template <typename T1, typename T2>
struct is_same {
  static const bool value = false;
};

template <typename T>
struct is_same<T, T> {
  static const bool value = true;
};

template <typename Target, typename Source>
Target lexical_cast(const Source &arg) {
  return lexical_cast_t<Target, Source, is_same<Target, Source>::value>::cast(arg);
}

int main()
{
  printf("int -> %s\n", lexical_cast<std::string>(100).c_str());
  printf("string -> %.2f\n", lexical_cast<double>("100"));

  return 0;
}
