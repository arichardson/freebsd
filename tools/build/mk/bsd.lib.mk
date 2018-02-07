# $FreeBSD$

.include "Makefile.boot"
# when bootstrapping we don't want to build shared libraries
NO_SHARED:=	yes
NO_PIC:=	yes
.include "../../../share/mk/bsd.lib.mk"
