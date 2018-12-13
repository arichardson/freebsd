# $FreeBSD$

.include "Makefile.boot"
.if ${.MAKE.OS} != "FreeBSD"
# Most Linux distributions don't ship the .a files for static linking.
# And on macOS it is impossible to create a statically linked binary.
NO_SHARED:=	no
NO_PIC:=	no
.endif
.include "../../../share/mk/bsd.prog.mk"

.include <bsd.linker.mk>
# When building with BFD we have to add libegacy.a at the end of linker
# command line again to ensure all symbols are resolved. LLD is smart enough
# to not need this. This happens e.g. when building compile_et (which
# adds -lvers at then end of the command line)
.if ${LINKER_TYPE} == "bfd"
LDADD+=	-lfreebsd -legacy
.endif
