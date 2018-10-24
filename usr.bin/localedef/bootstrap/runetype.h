#pragma once

#undef __size_t
#ifndef __FreeBSD__
typedef size_t __size_t;
#endif
#include "../../../include/runetype.h"
