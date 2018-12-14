# $FreeBSD$

.include <bsd.own.mk>

BINDIR=		${TESTSDIR}

NETBSD_ATF_TESTS_C=	fileactions_test
NETBSD_ATF_TESTS_C+=	spawn_test
NETBSD_ATF_TESTS_C+=	spawnattr_test

PROGS=		h_fileactions
PROGS+=		h_spawn
PROGS+=		h_spawnattr

SCRIPTS=	h_nonexec
SCRIPTS+=	h_zero

CLEANFILES+=	h_nonexec

.include "../../Makefile.netbsd-tests"

h_zero:
	dd_nostatus=`dd status=none count=0 2> /dev/null && echo status=none`; \
	    echo dd_nostatus=$${dd_nostatus}; \
	    dd if=/dev/zero of=h_zero bs=1k count=2 $${dd_nostatus}
	chmod a+x h_zero

CLEANFILES+=	h_zero

WARNS?=3

.include <bsd.test.mk>
