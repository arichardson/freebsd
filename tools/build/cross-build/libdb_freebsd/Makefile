LIB=	db-freebsd
NO_SHARED=	yes

INCS+=	${SRCTOP}/include/mpool.h \
		${SRCTOP}/include/ndbm.h
# Note: ${LIBC_SRCTOP}/db.h is explicitly not added here so that all cross-tools
# include ../include/common/db.h instead (which defines dbopen to __freebsd_dbopen)

MK_SYMVER=	no
LIBC_SRCTOP=	${SRCTOP}/lib/libc/
.include "${LIBC_SRCTOP}/db/Makefile.inc"
CFLAGS+=	-I ${.CURDIR}/../libc-bootstrap -Ddbopen=__freebsd_dbopen

# Should probably be in -legacy but since it depends on dbopen, let's just add
# the file here:
# for cap_mkdb:
.PATH: ${LIBC_SRCTOP}/gen
SRCS+=	getcap.c

.include <bsd.lib.mk>
