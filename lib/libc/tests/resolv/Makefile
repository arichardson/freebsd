# $FreeBSD$

.include <src.opts.mk>

PACKAGE=	tests

TESTSDIR=	${TESTSBASE}/lib/libc/resolv
WARNS=1
${PACKAGE}FILES+=		mach

ATF_TESTS_C+=	resolv_test
LIBC_SRCTOP=${SRCTOP}/lib/libc
.include "${SRCTOP}/lib/libc/resolv/Makefile.inc"
.include "${SRCTOP}/lib/libc/net/Makefile.inc"
.info "SRCS=${SRCS}"
SRCS:=${SRCS:Nrecv.c:Nsend.c:Nrcmd.c}
CONFS:=
# Note: this test relies on being dynamically linked.  You will get a
# spurious PASS for a statically linked test.
LIBADD.resolv_test+=	pthread
.PATH: ${SRCTOP}/lib/libmd
SRCS+=	md5c.c
.PATH: ${LIBC_SRCTOP}/isc
SRCS+=	ev_streams.c ev_timers.c
SRCS.resolv_test:=	${SRCS} resolv_test.c
SRCS:=
.if ${MACHINE_ARCH} == "amd64"
CFLAGS.resolv_test+=	-fsanitize=thread
CFLAGS.resolv_test+=	-g -ggdb -O1
LDADD.resolv_test+=	-fsanitize=thread
.include "${SRCTOP}/lib/libclang_rt/sanitizer-vars.mk"
LDADD.resolv_test+=	${SANITIZER_LDFLAGS}
.endif
CFLAGS.resolv_test+=	-Wthread-safety
CFLAGS.resolv_test+=	-I${SRCTOP}/lib/libc/include
CFLAGS.resolv_test+=	-Dlibc_dlopen=dlopen
CFLAGS.resolv_test+=	-D__libc_sigprocmask=sigprocmask




.include <bsd.test.mk>
