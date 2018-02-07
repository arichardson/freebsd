# $FreeBSD$

PACKAGE=lib${LIB}
LIB=	openbsd
SRCS=	getdtablecount.c \
	imsg-buffer.c \
	imsg.c \
	ohash.c
INTERNALLIB=

.if defined(BOOTSTRAPPING) && ${.MAKE.OS} != "FreeBSD"
# getdtablecount.c won't compile during bootstrap for Linux, but it seems like
# it is not used by any of the cross tools so just skipping it works fine
SRCS:=${SRCS:Ngetdtablecount.c}
.endif

CFLAGS+= -I${.CURDIR}

WARNS=	3

.include <bsd.lib.mk>
