/*-
 * SPDX-License-Identifier: BSD-3-Clause
 *
 * Copyright (c) 1992, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#if defined(LIBC_SCCS) && !defined(lint)
static char sccsid[] = "@(#)qsort.c	8.1 (Berkeley) 6/4/93";
#endif /* LIBC_SCCS and not lint */
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <errno.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "libc_private.h"

#if defined(I_AM_QSORT_R)
typedef int		 cmp_t(void *, const void *, const void *);
#elif defined(I_AM_QSORT_S)
typedef int		 cmp_t(const void *, const void *, void *);
#else
typedef int		 cmp_t(const void *, const void *);
#endif
static inline char	*med3(char *, char *, char *, cmp_t *, void *);

#define	MIN(a, b)	((a) < (b) ? a : b)

/*
 * Qsort routine from Bentley & McIlroy's "Engineering a Sort Function".
 */

static inline void
swapfunc(char *a, char *b, size_t es)
{
	char t;

	do {
		t = *a;
		*a++ = *b;
		*b++ = t;
	} while (--es > 0);
}

#define	vecswap(a, b, n)				\
	if ((n) > 0) swapfunc(a, b, n)

#if defined(I_AM_QSORT_R)
#define	CMP(t, x, y) (cmp((t), (x), (y)))
#elif defined(I_AM_QSORT_S)
#define	CMP(t, x, y) (cmp((x), (y), (t)))
#else
#define	CMP(t, x, y) (cmp((x), (y)))
#endif

static inline char *
med3(char *a, char *b, char *c, cmp_t *cmp, void *thunk
#if !defined(I_AM_QSORT_R) && !defined(I_AM_QSORT_S)
__unused
#endif
)
{
	return CMP(thunk, a, b) < 0 ?
	       (CMP(thunk, b, c) < 0 ? b : (CMP(thunk, a, c) < 0 ? c : a ))
	      :(CMP(thunk, b, c) > 0 ? b : (CMP(thunk, a, c) < 0 ? a : c ));
}

#if defined(I_AM_QSORT_R)
void __attribute__((__visibility__("protected")))
qsort_r(void *a, size_t n, size_t es, void *thunk, cmp_t *cmp)
#elif defined(I_AM_QSORT_S)
errno_t __attribute__((__visibility__("protected")))
qsort_s(void *a, rsize_t n, rsize_t es, cmp_t *cmp, void *thunk)
#else
#define	thunk NULL
void __attribute__((__visibility__("protected")))
qsort(void *a, size_t n, size_t es, cmp_t *cmp)
#endif
{
	char *pa, *pb, *pc, *pd, *pl, *pm, *pn;
	size_t d1, d2;
	int cmp_result;
	int swap_cnt;

#ifdef I_AM_QSORT_S
	if (n > RSIZE_MAX) {
		__throw_constraint_handler_s("qsort_s : n > RSIZE_MAX", EINVAL);
		return (EINVAL);
	} else if (es > RSIZE_MAX) {
		__throw_constraint_handler_s("qsort_s : es > RSIZE_MAX", EINVAL);
		return (EINVAL);
	} else if (n != 0) {
		if (a == NULL) {
			__throw_constraint_handler_s("qsort_s : a == NULL", EINVAL);
			return (EINVAL);
		} else if (cmp == NULL) {
			__throw_constraint_handler_s("qsort_s : cmp == NULL", EINVAL);
			return (EINVAL);
		}
	}
#endif

loop:
	swap_cnt = 0;
	if (n < 7) {
		for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
			for (pl = pm; 
			     pl > (char *)a && CMP(thunk, pl - es, pl) > 0;
			     pl -= es)
				swapfunc(pl, pl - es, es);
#ifdef I_AM_QSORT_S
		return (0);
#else
		return;
#endif
	}
	pm = (char *)a + (n / 2) * es;
	if (n > 7) {
		pl = a;
		pn = (char *)a + (n - 1) * es;
		if (n > 40) {
			size_t d = (n / 8) * es;

			pl = med3(pl, pl + d, pl + 2 * d, cmp, thunk);
			pm = med3(pm - d, pm, pm + d, cmp, thunk);
			pn = med3(pn - 2 * d, pn - d, pn, cmp, thunk);
		}
		pm = med3(pl, pm, pn, cmp, thunk);
	}
	swapfunc(a, pm, es);
	pa = pb = (char *)a + es;

	pc = pd = (char *)a + (n - 1) * es;
	for (;;) {
		while (pb <= pc && (cmp_result = CMP(thunk, pb, a)) <= 0) {
			if (cmp_result == 0) {
				swap_cnt = 1;
				swapfunc(pa, pb, es);
				pa += es;
			}
			pb += es;
		}
		while (pb <= pc && (cmp_result = CMP(thunk, pc, a)) >= 0) {
			if (cmp_result == 0) {
				swap_cnt = 1;
				swapfunc(pc, pd, es);
				pd -= es;
			}
			pc -= es;
		}
		if (pb > pc)
			break;
		swapfunc(pb, pc, es);
		swap_cnt = 1;
		pb += es;
		pc -= es;
	}
	if (swap_cnt == 0) {  /* Switch to insertion sort */
		for (pm = (char *)a + es; pm < (char *)a + n * es; pm += es)
			for (pl = pm; 
			     pl > (char *)a && CMP(thunk, pl - es, pl) > 0;
			     pl -= es)
				swapfunc(pl, pl - es, es);
#ifdef I_AM_QSORT_S
		return (0);
#else
		return;
#endif
	}

	pn = (char *)a + n * es;
	d1 = MIN(pa - (char *)a, pb - pa);
	vecswap(a, pb - d1, d1);
	d1 = MIN(pd - pc, pn - pd - es);
	vecswap(pb, pn - d1, d1);

	d1 = pb - pa;
	d2 = pd - pc;
	if (d1 <= d2) {
		/* Recurse on left partition, then iterate on right partition */
		if (d1 > es) {
#if defined(I_AM_QSORT_R)
			qsort_r(a, d1 / es, es, thunk, cmp);
#elif defined(I_AM_QSORT_S)
			qsort_s(a, d1 / es, es, cmp, thunk);
#else
			qsort(a, d1 / es, es, cmp);
#endif
		}
		if (d2 > es) {
			/* Iterate rather than recurse to save stack space */
			/* qsort(pn - d2, d2 / es, es, cmp); */
			a = pn - d2;
			n = d2 / es;
			goto loop;
		}
	} else {
		/* Recurse on right partition, then iterate on left partition */
		if (d2 > es) {
#if defined(I_AM_QSORT_R)
			qsort_r(pn - d2, d2 / es, es, thunk, cmp);
#elif defined(I_AM_QSORT_S)
			qsort_s(pn - d2, d2 / es, es, cmp, thunk);
#else
			qsort(pn - d2, d2 / es, es, cmp);
#endif
		}
		if (d1 > es) {
			/* Iterate rather than recurse to save stack space */
			/* qsort(a, d1 / es, es, cmp); */
			n = d1 / es;
			goto loop;
		}
	}

#ifdef I_AM_QSORT_S
	return (0);
#endif
}
