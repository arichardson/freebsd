#pragma once

#include "../../../include/locale.h"

#ifdef __GLIBC__
/* This is needed to include stddef.h, etc */
typedef struct __locale_struct * __locale_t;
#endif
