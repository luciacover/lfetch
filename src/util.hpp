#ifndef UTIL_HPP_
#define UTIL_HPP_

#include <string>

struct sysinfo_t {
  std::string kernel_name;
  std::string distro;
  std::string hostname;
  std::string login;
};

#endif // UTIL_HPP_
