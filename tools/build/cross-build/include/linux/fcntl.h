#pragma once

#define open __open
#include_next <fcntl.h>
#include <sys/file.h>


#ifndef O_EXLOCK
#define O_EXLOCK (1 << 30)
#endif
#ifndef O_SHLOCK
#define O_SHLOCK (1 << 31)
#endif


#undef open
#define open(path, flags, ...) ({ \
    int __fd = __open(path, flags, ##__VA_ARGS__); \
    if (flags & O_EXLOCK) flock(__fd, LOCK_EX); \
    if (flags & O_SHLOCK) flock(__fd, LOCK_SH); \
    __fd; })
