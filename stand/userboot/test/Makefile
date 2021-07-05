# $FreeBSD$

# Unlike the other programs in stand this links the normal userspace libraries
# so we have to ensure MK_ASAN/MK_UBSAN matches the default to avoid linker
# errors (this assignment prevents stand/Makefile.inc from setting MK_ASAN=no).
_USE_DEFAULT_USERSPACE_LIBS=yes

.include <bsd.init.mk>

PROG=		test
INTERNALPROG=

CFLAGS=	-I${BOOTSRC}/userboot

.include <bsd.prog.mk>
