#pragma once

#include_next <unistd.h>
#include <stdlib.h>
#include <string.h>
#undef getopt

__BEGIN_DECLS

// Force POSIX compatibility in glibc getopt
static inline int getopt_real(int argc, char * const argv[], const char *optstring)
{
#ifdef __GLIBC__
	// If the first character of optstring is '+' or the environment variable
	// POSIXLY_CORRECT is set, then option processing stops as soon as a
	// nonoption argument is encountered.
	char* newoptstring = NULL;
	asprintf(&newoptstring, "+%s", optstring);
	int ret = bsd_getopt(argc, argv, newoptstring);
	free(newoptstring);
	return ret;
#else
	return bsd_getopt(argc, argv, optstring)
#endif
}

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

#define getopt getopt_real

/* Used by elftoolchain: */
extern char *program_invocation_name;
extern char *program_invocation_short_name;

__END_DECLS
