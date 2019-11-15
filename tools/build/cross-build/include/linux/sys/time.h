#pragma once

#include_next <sys/time.h>
#ifdef _OPENSOLARIS_SYS_TIME_H_
/* Not quite the same but should be good enough for CDDL bootstrap tools */
#include <time.h>
#define CLOCK_UPTIME CLOCK_BOOTTIME
#endif
