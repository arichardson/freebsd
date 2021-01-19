# $FreeBSD$

# Sanitizers won't work for stand
MK_MSAN:=no
MK_ASAN:=no
MK_UBSAN:=no

SUBDIR_PARALLEL=	yes

.include "defs.mk"
