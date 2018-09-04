#pragma once
#include </usr/include/limits.h>
#include_next <limits.h>
#include <sys/types.h>

#define MAXBSIZE        65536   /* must be power of 2 */
#ifndef __OFF_T_MATCHES_OFF64_T
#error "Expected 64-bit off_t"
#endif
#define OFF_MAX UINT64_MAX
#define QUAD_MAX INT64_MAX

#ifndef GID_MAX
#define GID_MAX ((gid_t)-1)
#endif


#ifndef UID_MAX
#define UID_MAX ((uid_t)-1)
#endif


#ifndef _GNU_SOURCE
#error _GNU_SOURCE not defined
#endif

#ifndef __USE_POSIX
#warning __USE_POSIX not defined
#endif

#ifndef _POSIX_PATH_MAX
#error _POSIX_PATH_MAX should be defined
#endif

#if defined __GNUC__ && !defined _GCC_LIMITS_H_
#error "GCC limits not included"
#endif
