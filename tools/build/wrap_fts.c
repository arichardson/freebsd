/*-
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright 2020 Alex Richardson <arichardson@FreeBSD.org>
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory (Department of Computer Science and
 * Technology) under DARPA contract HR0011-18-C-0016 ("ECATS"), as part of the
 * DARPA SSITH research programme.
 *
 * This software was developed by SRI International and the University of
 * Cambridge Computer Laboratory under DARPA/AFRL contract (FA8750-10-C-0237)
 * ("CTSRD"), as part of the DARPA CRASH research programme.
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
#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include <sys/stat.h>

#include <fts.h>
#include <stdio.h>

#if __has_feature(memory_sanitizer)
/* Work around missing MSAN interceptors for fts(): */
#include <sanitizer/msan_interface.h>

FTS *__real_fts_open(char *const *, int,
    int (*)(const FTSENT *const *, const FTSENT *const *));

FTSENT *__real_fts_read(FTS *);

FTS *
__wrap_fts_open(char *const *argv, int options,
    int (*compar)(const FTSENT *const *, const FTSENT *const *))
{
	FTS *result = __real_fts_open(argv, options, compar);
	if (result) {
		__msan_unpoison(result, sizeof(*result));
	}
	return result;
}

FTSENT *
__wrap_fts_read(FTS *sp)
{
	FTSENT *result = __real_fts_read(sp);
    // Missing interceptor for fts_read:
	if (result) {
		__msan_unpoison(result, sizeof(*result));
		__msan_unpoison(result->fts_statp, sizeof(*result->fts_statp));
		__msan_unpoison(result->fts_name, result->fts_namelen + 1);
		__msan_unpoison(result->fts_path, result->fts_pathlen + 1);
	}
	return result;
}

#endif
