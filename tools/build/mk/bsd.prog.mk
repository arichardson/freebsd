# $FreeBSD$

.include "Makefile.boot"
.if ${.MAKE.OS} != "FreeBSD"
# Most Linux distributions don't ship the .a files for static linking.
# And on macOS it is impossible to create a statically linked binary.
NO_SHARED:=	no
NO_PIC:=	no
.endif
.include "../../../share/mk/bsd.prog.mk"
