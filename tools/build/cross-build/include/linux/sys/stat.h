#pragma once
/*
 * glibc shipped with Ubuntu 16.04 doesn't include a definition of
 * struct timespec when sys/stat.h is included
 * */
#define __need_timespec
#include <time.h>

// <stat.h> contains a member __unused
#ifdef __unused
#undef __unused
#define __unused_undefd
#endif

#include_next <sys/stat.h>

#ifdef __unused_undefd
#undef __unused_undefd
#define __unused __attribute__((unused))
#endif

#define st_atimensec st_atim.tv_nsec
#define st_mtimensec st_mtim.tv_nsec
#define st_ctimensec st_ctim.tv_nsec

#define st_atimespec st_atim
#define st_mtimespec st_mtim
#define st_ctimespec st_ctim
