#pragma once
#include_next <sys/time.h>

#ifdef _OPENSOLARIS_SYS_TIME_H_
#include <time.h>
#ifndef CLOCK_UPTIME
#define CLOCK_UPTIME CLOCK_UPTIME_RAW
#endif
#endif
