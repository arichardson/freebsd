
// Note: getopt.h is included multiple times by glibc so we can't use #pragma once here
#include_next <getopt.h>

__BEGIN_DECLS
int __freebsd_getopt(int argc, char * const argv[], const char *shortopts);
__END_DECLS

#undef getopt
#define getopt(argc, argv, optstr) __freebsd_getopt(argc, argv, optstr)
