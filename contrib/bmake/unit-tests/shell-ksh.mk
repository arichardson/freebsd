# $NetBSD: shell-ksh.mk,v 1.1 2020/10/03 14:39:36 rillig Exp $
#
# Tests for using a korn shell for running the commands.

_ksh!=command -v ksh || echo /bin/sh
.SHELL: name="ksh" path="${_ksh}"

all:
	: normal
	@: hidden
	+: always
	-: ignore errors
