# $FreeBSD$

.PATH: ${.CURDIR:H}/common

SRCS=		crti.S crtn.S
OBJS=		${SRCS:N*.h:R:S/$/.o/g}
OBJS+=		gcrt1.o crt1.o Scrt1.o
CFLAGS+=	-I${.CURDIR} -I${.CURDIR:H}/common \
		-I${SRCTOP}/lib/libc/include
CFLAGS+=	-DCRT_IRELOC_REL

FILES=		${OBJS}
FILESMODE=	${LIBMODE}
FILESOWN=	${LIBOWN}
FILESGRP=	${LIBGRP}
FILESDIR=	${LIBDIR}
# These FILES qualify as libraries for the purpose of LIBRARIES_ONLY.
.undef LIBRARIES_ONLY

CLEANFILES=	${OBJS} crt1.s gcrt1.s Scrt1.s

# See the comment in lib/csu/common/crtbrand.c for the reason crt1.c is not
# directly compiled to .o files.


gcrt1.s: crt1.c
	${CC} ${CFLAGS} -DGCRT -S -o ${.TARGET} ${.CURDIR}/crt1.c
	sed ${SED_FIX_NOTE} ${.TARGET}

gcrt1.o: gcrt1.s
	${CC} ${CFLAGS:N-g} ${ACFLAGS} -c -o ${.TARGET} gcrt1.s

crt1.s: crt1.c
	${CC} ${CFLAGS} -S -o ${.TARGET} ${.CURDIR}/crt1.c
	sed ${SED_FIX_NOTE} ${.TARGET}

crt1.o: crt1.s
	${CC} ${CFLAGS:N-g} ${ACFLAGS} -c -o ${.TARGET} crt1.s

Scrt1.s: crt1.c
	${CC} ${CFLAGS} -fPIC -DPIC -S -o ${.TARGET} ${.CURDIR}/crt1.c
	sed ${SED_FIX_NOTE} ${.TARGET}

Scrt1.o: Scrt1.s
	${CC} ${CFLAGS:N-g} ${ACFLAGS} -c -o ${.TARGET} Scrt1.s

.include <bsd.lib.mk>
