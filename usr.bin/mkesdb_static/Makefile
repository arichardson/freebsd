# $FreeBSD$

.PATH: ${SRCTOP}/lib/libc/iconv ${SRCTOP}/usr.bin/mkesdb

PROG=	mkesdb_static
SRCS=	citrus_bcs.c citrus_db_factory.c citrus_db_hash.c \
	citrus_lookup_factory.c
MAN=
.if !defined(BOOSTRAPPING)
# None of the other bootstrap tools are built static and this breaks ASAN.
NO_SHARED= yes
.endif
NO_WMISSING_VARIABLE_DECLARATIONS=

build-tools: mkesdb_static

.include "${SRCTOP}/usr.bin/mkesdb/Makefile.inc"
.include <bsd.prog.mk>

${PROG}: ${BUILD_TOOLS_META}
