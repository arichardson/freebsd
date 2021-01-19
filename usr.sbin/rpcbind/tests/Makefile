# $FreeBSD$

.include <src.opts.mk>

.PATH:	${.CURDIR}/..

ATF_TESTS_C=	addrmerge_test
CFLAGS+=	-I${.CURDIR:H} -Wno-cast-qual
SRCS.addrmerge_test=	addrmerge_test.c util.c

.if ${MK_INET6_SUPPORT} != "no"
CFLAGS+= -DINET6
.endif

WARNS?=	3

.if ${MK_ASAN} != "no"
# Work around "error: duplicate symbol: getifaddrs" since ASAN also defines it.
LDFLAGS+=-shared-libasan
.endif

.include <bsd.test.mk>
