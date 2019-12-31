#pragma once

#include_next <sys/types.h>

#ifndef __size_t
typedef __SIZE_TYPE__ __size_t;
#endif

typedef __builtin_va_list __va_list;
