#pragma once

#include_next <getopt.h>

__BEGIN_DECLS

#undef getopt
#define getopt(argc, argv, optstr) bsd_getopt(argc, argv, optstr)
int bsd_getopt(int argc, char * const argv[], const char *shortopts);

__END_DECLS
