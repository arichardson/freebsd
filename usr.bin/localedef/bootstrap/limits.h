#pragma once

#include_next <limits.h>

/* Fix boostrapping from older systems/non-FreeBSD systems */
#undef COLL_WEIGHTS_MAX
#define COLL_WEIGHTS_MAX 10
