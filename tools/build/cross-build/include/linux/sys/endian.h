#pragma once
#include_next <sys/endian.h>

#ifndef bswap64
#define bswap64(a) __builtin_bswap64(a)
#endif

#ifndef bswap32
#define bswap32(a) __builtin_bswap32(a)
#endif

#ifndef bswap16
#define bswap16(a) __builtin_bswap16(a)
#endif
