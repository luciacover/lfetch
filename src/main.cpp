#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "util.hpp"

int get_kernel(sysinfo_t *sysinfo);
int get_hostname(sysinfo_t *sysinfo);
int get_login(sysinfo_t *sysinfo);

int main(int argc, char **argv) {
  sysinfo_t sys;

  /* theres absolutely no way this is the best way to do this, i should
     probably use something more idiomatic for C++  */
  const int kernel_res   = get_kernel(&sys);
  const int hostname_res = get_hostname(&sys);
  const int login_res    = get_login(&sys);

  if (kernel_res || hostname_res || login_res) {
    exit(-1);
  }
  
  printf("kernel: %s\nhostname: %s@%s\n", sys.kernel_name.c_str(),
                                          sys.login.c_str(),
                                          sys.hostname.c_str());
  
  return 0;
}

int get_kernel(sysinfo_t *sysinfo) {
  utsname uts = { 0 };

  const int result = uname(&uts);

  if (result) {
    perror("error with uname");
    return result;
  }

  sysinfo->kernel_name = uts.sysname;
  return 0;
}

int get_hostname(sysinfo_t *sysinfo) {
  const long MAX_HOSTNAME = sysconf(_SC_HOST_NAME_MAX);
  char *hostname = (char *)malloc(MAX_HOSTNAME * sizeof(char));

  const int result = gethostname(hostname, MAX_HOSTNAME);

  if (result) {
    perror("error with gethostname");
    return result;
  }

  sysinfo->hostname = hostname;
  
  free(hostname); /* this might be a use after free? i get no junk, but idk */
  return 0;  
}

int get_login(sysinfo_t *sysinfo) {
  const long MAX_LOGIN = sysconf(_SC_LOGIN_NAME_MAX);
  char *login = (char *)malloc(MAX_LOGIN * sizeof(char));

  int result = getlogin_r(login, MAX_LOGIN);

  if (result) {
    perror("error getting login");
    return result;
  }

  sysinfo->login = login;
  
  free(login);
  return 0;
}
