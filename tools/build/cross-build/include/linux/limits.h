#pragma once

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include_next <limits.h>
#include <sys/types.h>

#if __has_include(<linux/limits.h>)
#include <linux/limits.h>
#endif

#ifndef MAXBSIZE
#define MAXBSIZE        65536   /* must be power of 2 */
#endif

#ifndef OFF_MAX
#define OFF_MAX UINT64_MAX
#endif

#ifndef QUAD_MAX
#define QUAD_MAX INT64_MAX
#endif

#ifndef GID_MAX
#define GID_MAX ((gid_t)-1)
#endif


#ifndef UID_MAX
#define UID_MAX ((uid_t)-1)
#endif


#ifdef __GLIBC__

/* Sanity checks for glibc */
#ifndef _GNU_SOURCE
#error _GNU_SOURCE not defined
#endif

#ifndef __USE_POSIX
#warning __USE_POSIX not defined
#endif

#if defined __GNUC__ && !defined _GCC_LIMITS_H_
#error "GCC limits not included"
#endif

#ifndef __OFF_T_MATCHES_OFF64_T
#error "Expected 64-bit off_t"
#endif

#endif

#ifndef _POSIX_PATH_MAX
#define _POSIX_PATH_MAX PATH_MAX
// #error _POSIX_PATH_MAX should be defined
#endif
