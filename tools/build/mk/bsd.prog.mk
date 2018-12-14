# $FreeBSD$

.include "Makefile.boot.pre"
.include "../../../share/mk/bsd.prog.mk"
.include "Makefile.boot"

.include <bsd.linker.mk>

.if ${.MAKE.OS} != "FreeBSD" && ${LINKER_TYPE} == "bfd"
# When building with BFD we have to add libegacy.a at the end of linker
# command line again to ensure all symbols are resolved. LLD is smart enough
# to not need this. This happens e.g. when building compile_et (which
# adds -lvers at then end of the command line).
LDADD+=	-lfreebsd -legacy
.endif
