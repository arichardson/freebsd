#pragma once

/* one some version of glibc including string.h before stdlib.h won't work.
 * This happens when building anything that uses the libnetbsd stdlib.h override.
 * This is because string.h will include stdlib.h with a flag set to define
 * only a subset of the functions (which will then not set the _STDLIB_H
 * macro. libnetbsd stdlib.h can only be included once so this will not work.
 */
#include <stdlib.h>
#include_next <string.h>
