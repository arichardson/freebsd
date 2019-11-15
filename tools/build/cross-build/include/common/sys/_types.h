#pragma once

#if __has_include_next(<sys/_types.h>)
#include_next <sys/_types.h>
#else
#include <sys/types.h>
#endif

/* Neither GLibc nor macOS define __va_list but many FreeBSD headers require it */
typedef __builtin_va_list __va_list;

