#pragma once
#include_next <sys/endian.h>


/* Ensure all these are constant expressions (which is not the case for some
 * of the glibc versions depending on compiler optimization level) */

#undef bswap64
#define bswap64(a) __builtin_bswap64(a)

#undef bswap32
#define bswap32(a) __builtin_bswap32(a)

#undef bswap16
#define bswap16(a) __builtin_bswap16(a)

#undef __bswap_64
#define __bswap_64(a) __builtin_bswap64(a)

#undef __bswap_32
#define __bswap_32(a) __builtin_bswap32(a)

#undef __bswap_16
#define __bswap_16(a) __builtin_bswap16(a)
