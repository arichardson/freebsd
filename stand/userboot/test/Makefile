# $FreeBSD$

.include <bsd.init.mk>

PROG=		test
INTERNALPROG=
# Needed as a workaround for sanitizer builds...
NO_SHARED=yes

CFLAGS=	-I${BOOTSRC}/userboot

.include <bsd.prog.mk>
