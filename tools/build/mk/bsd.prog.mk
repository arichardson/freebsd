# $FreeBSD$

.include "Makefile.boot"
.if ${.MAKE.OS} != "FreeBSD"
# Most Linux distributions don't ship the .a files for static linking.
# And on macOS it is impossible to create a statically linked binary.
NO_SHARED:=	no
NO_PIC:=	no
.endif
.include "../../../share/mk/bsd.prog.mk"

# When building on Linux we need to add libbsd to the linker commmand line
# If it is a static library we need to add it as the last linker argument since
# otherwise we get linker errors with bfd due to libraries being added at the
# end depending on libbsd (it must also come after libegacy since that depends
# on libbsd).
.if ${.MAKE.OS} == "Linux"
.if ${LIBBSD_DIR} == "/usr"
# If it is installed in /usr it's probably a shared libraries so use -lbds
LDADD+=	-lbsd
.else
LDADD+=	${LIBBSD_DIR}/lib/libbsd.a
.endif
.endif  # LINUX
