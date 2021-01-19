#	@(#)Makefile	8.1 (Berkeley) 6/6/93
# $FreeBSD$

# sed is extremely slow with MSan+UBSan, skip it for the bootstrap tools
NO_MSAN=yes	# must be set before bsd.init.mk
.include <src.opts.mk>

PACKAGE=	runtime
PROG=	sed
SRCS=	compile.c main.c misc.c process.c

HAS_TESTS=
SUBDIR.${MK_TESTS}+= tests

.include <bsd.prog.mk>
