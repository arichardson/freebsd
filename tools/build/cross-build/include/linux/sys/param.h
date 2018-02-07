#pragma once
#include_next <sys/param.h>

/* `getconf LOGIN_NAME_MAX` prints 256 on Ubuntu 16.04 but
 * let's use 32 since that will work across all systems
 */
#define MAXLOGNAME	33		/* max login name length (incl. NUL) */
