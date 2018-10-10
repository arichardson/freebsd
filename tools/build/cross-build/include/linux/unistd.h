#pragma once

#ifndef __USE_POSIX2
// Ensure that unistd.h pulls in getopt
#define __USE_POSIX2
#endif
#include_next <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#ifndef required_argument
#error"something went wrong including getopt"
#endif

__BEGIN_DECLS

static inline int issetugid(void) {
	return 0;
}

static inline char *
fflagstostr(u_long flags)
{
	return strdup("");
}

static inline int
strtofflags(char **stringp, u_long *setp, u_long *clrp) {
	/* On linux just ignore the file flags for now */
	/*
	 * XXXAR: this will prevent makefs from setting noschg on libc, etc
	 * so we should really build the version from libc
	 */
	if (setp)
		*setp = 0;
	if (clrp)
		*clrp = 0;
	return 0; /* success */
}

/* Used by elftoolchain: */
extern char *program_invocation_name;
extern char *program_invocation_short_name;

__END_DECLS
