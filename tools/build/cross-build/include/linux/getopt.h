#pragma once

#warning "LINUX getopt"
#include_next <getopt.h>
#warning "after include_next getopt"

__BEGIN_DECLS

#undef getopt
#define getopt(argc, argv, optstr) bsd_getopt(argc, argv, optstr)
int bsd_getopt(int argc, char * const argv[], const char *shortopts);

__END_DECLS
