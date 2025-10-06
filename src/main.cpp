#include <cstring>
#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.hpp"

int get_kernel(sysinfo_t *sysinfo);

int main(int argc, char **argv) {
  sysinfo_t sys;
  if (get_kernel(&sys)) {
    perror("error getting uname");
  }

  printf("%s\n", sys.kernel_name.c_str());
  
  return 0;
}

int get_kernel(sysinfo_t *sysinfo) {
  utsname uts = { 0 };

  int result = uname(&uts);

  if (result) {
    perror("error with uname");
    return result;
  }

  sysinfo->kernel_name = uts.sysname;
  return 0;
}
