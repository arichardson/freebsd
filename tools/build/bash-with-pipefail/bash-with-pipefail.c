/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright 2018 Alex Richardson <arichardson@FreeBSD.org>
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

#include <err.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sysexits.h>

/*
 * Start bash with -o pipefail to catch errors.
 * This is used when building world on a non-FreeBSD host to ensure that we
 * don't depend on binaries that don't exist and are used in pipeline.
 * Without -o pipefail missing commands in a pipeline are ignored and can
 * cause empty input files to be generated.
 */
int main(int argc, char** argv) {
	char** new_argv;
	char* bash_path;

	new_argv = calloc(argc + 3, sizeof(char*));
	new_argv[0] = "bash"; /* bash won't support -o pipefail in sh mode */
	new_argv[1] = "-eo";
	new_argv[2] = "pipefail";

	for (int i = 1; i < argc; i++)
		new_argv[i + 2] = argv[i];
	new_argv[argc + 2] = NULL;

	/*
	 * Since we are running with a restricted $PATH, we will not be able
	 * to find bash in $PATH. Try /usr/local/bin and /bin first
	 */
	if (access("/usr/local/bin/bash", F_OK) == 0)
		bash_path = "/usr/local/bin/bash";
	else if (access("/bin/bash", F_OK) == 0)
		bash_path = "/bin/bash";
	else
		errx(EX_OSFILE, "Could not infer path to bash");

	if (execvp(bash_path, new_argv) != 0)
		err(EX_UNAVAILABLE, "Could not execute %s", bash_path);
}
