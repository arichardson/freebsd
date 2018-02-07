#pragma once
#include_next <sys/cdefs.h>

#ifndef __FBSDID
#define __FBSDID(id)
#endif

#ifndef __IDSTRING
#define __IDSTRING(name,string)
#endif

#ifndef rounddown
// needed by libsbuf
#define	rounddown(x, y)	(((x)/(y))*(y))
#define	rounddown2(x, y) ((x)&(~((y)-1)))          /* if y is power of two */
#define	roundup(x, y)	((((x)+((y)-1))/(y))*(y))  /* to any y */
#define	roundup2(x, y)	(((x)+((y)-1))&(~((y)-1))) /* if y is powers of two */
#define powerof2(x)	((((x)-1)&(x))==0)
#endif

#ifndef __va_list
#include <stdarg.h>
#define __va_list va_list
#endif

#ifndef __pure
#define __pure __attribute__((__pure__))
#endif

#ifndef __packed
#define __packed __attribute__((__packed__))
#endif

#ifndef __printf0like
#define	__printf0like(fmtarg, firstvararg) \
	    __attribute__((__format__ (__printf0__, fmtarg, firstvararg)))
#endif

#ifndef __weak_reference
#define __weak_reference(sym,alias)	\
    static int alias() __attribute__ ((weakref (#sym)));
#endif

#ifndef __malloc_like
#define	__malloc_like	__attribute__((__malloc__))
#endif

#ifndef nitems
// https://stackoverflow.com/questions/1598773/is-there-a-standard-function-in-c-that-would-return-the-length-of-an-array/1598827#1598827
#define nitems(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))
#endif

#ifndef __min_size
#if !defined(__cplusplus)
#define __min_size(x)   static (x)
#else
#define __min_size(x)   (x)
#endif
#endif

#ifndef __unused
#define __unused __attribute__((unused))
#endif
#define __format_arg(fmtarg)    __attribute__((__format_arg__ (fmtarg)))

#ifndef __exported
#define	__exported	__attribute__((__visibility__("default")))
#endif
#ifndef __hidden
#define	__hidden	__attribute__((__visibility__("hidden")))
#endif

/*
 * These should probably be in sys/types.h but mtree expects them to exist
 * without including <sys/types.h>
 */
typedef	unsigned char	u_char;
typedef	unsigned short	u_short;
typedef	unsigned int	u_int;
typedef	unsigned long	u_long;

/* This is needed so that BSNMP doesn't redeclare an incompatible version */
#define HAVE_STRLCPY 1
/* The compiler supports __func__ */
#define HAVE_DECL___FUNC__ 1

/* On MacOS __CONCAT is defined as x ## y, which won't expand macros */
#undef __CONCAT
#define	__CONCAT1(x,y)	x ## y
#define	__CONCAT(x,y)	__CONCAT1(x,y)
