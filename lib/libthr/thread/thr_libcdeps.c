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
 * This work was supported by Innovate UK project 105694, "Digital Security by
 * Design (DSbD) Technology Platform Prototype".
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifdef AVOID_INTERPOSABLE_LIBC_FUNCTIONS
#include <sys/cdefs.h>
#include <stddef.h>

void *memcpy(void *, const void *, size_t) __hidden;
void *memmove(void *, const void *, size_t) __hidden;
void *memset(void *, int, size_t) __hidden;

/*
 * This file exists to avoid interposable calls to libc functions inside
 * functions that are intercepted by sanitizer runtimes. One example where we
 * need to avoid interposable function calls is the copy of the ucontext_t
 * argument in handle_signal() as this results in crashes when linking
 * applications with ThreadSanitizer. Another example is the libthr-internal
 * allocator that calls memset and memcpy. With interposable function calls
 * ThreadSanitizer reports false-positive race conditions since the locks
 * guarding the allocation functions cannot be seen by the TSan runtime.
 *
 * Note: This file is only needed for the shared library build.
 */
#include "../../libc/string/memmove.c"
__strong_reference(memmove, memcpy);
#include "../../libc/string/memset.c"

#endif
