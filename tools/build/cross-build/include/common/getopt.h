/* can be included more than once */
/* #pragma once */

/* Since we are building the FreeBSD getopt.c also use the matching header */
#include "../../../../../include/getopt.h"

#define getopt_long __freebsd_getopt_long
#define getopt_long_only __freebsd_getopt_long_only
extern int __freebsd_opterr;
#define opterr __freebsd_opterr
extern int __freebsd_optind;
#define optind __freebsd_optind
extern int __freebsd_optopt;
#define optopt __freebsd_optopt
extern int __freebsd_optreset;
#define optreset __freebsd_optreset
extern char* __freebsd_optarg;
#define optarg __freebsd_optarg


#undef getopt
#define getopt(argc, argv, optstr) __freebsd_getopt(argc, argv, optstr)
