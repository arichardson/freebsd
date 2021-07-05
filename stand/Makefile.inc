# $FreeBSD$

.if !defined(_USE_DEFAULT_USERSPACE_LIBS)
# Sanitizers won't work for stand (except for userboot/test).
MK_ASAN:=no
MK_UBSAN:=no
.endif

SUBDIR_PARALLEL=	yes

.include "defs.mk"
