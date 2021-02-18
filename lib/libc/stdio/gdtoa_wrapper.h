/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright 2021 Alex Richardson <arichardson@FreeBSD.org>
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
 *
 * This work was supported by Innovate UK project 105694, "Digital Security by
 * Design (DSbD) Technology Platform Prototype".
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
/* Avoid references to fenv functions by requiring them to be always_inline. */
#ifdef _FENV_H_
#error "fenv.h was already included"
#endif
#define	__fenv_static static __always_inline
#include <fenv.h>

#include "gdtoaimp.h"
/*
 * For soft-float code, the fenv functions are defined out-of-line in libm,
 * so we must avoid references to them inisde libc. We therefore only mask the
 * FE_INEXACT flag for hard-float architectures.
 */
#ifndef SOFTFLOAT_FOR_GCC
#undef dtoa
#undef gdtoa

/*
 * Mask the inexact flag that can be set by dtoa due to (k = (int)ds;) to
 * prevent printf() from changing the floating point exception flags.
 */
#define	dtoa(...) ({					\
	/* TODO: _Pragma("STDC FENV_ACCESS ON"); */	\
	int was_inexact = fetestexcept(FE_INEXACT);	\
	char *result = __dtoa(__VA_ARGS__);		\
	if (!was_inexact)				\
		feclearexcept(FE_INEXACT);		\
	result; })
#define	gdtoa(...) ({					\
	/* TODO: _Pragma("STDC FENV_ACCESS ON"); */	\
	int was_inexact = fetestexcept(FE_INEXACT);	\
	char *result = __gdtoa(__VA_ARGS__);		\
	if (!was_inexact)				\
		feclearexcept(FE_INEXACT);		\
	result; })
#endif
