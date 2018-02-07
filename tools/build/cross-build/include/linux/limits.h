#pragma once
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
