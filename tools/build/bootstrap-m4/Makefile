
.PATH: ${SRCTOP}/usr.bin/m4 ${.CURDIR}
# Build a bootstrap version of m4 (needed in order to build libelf and lex)
all: bootstrap

BINDIR=	/usr/bin
.include "${SRCTOP}/usr.bin/m4/Makefile"

bootstrap: ${GENFILES:S/^/init/g}
	echo "BOOTSTRAP ${GENFILES:S/^/init/g}"
.for _f in ${GENFILES}
	@cmp -s ${.CURDIR}/init${_f} ${_f} || { \
		echo "Bootstrapping ${_f}" ; \
		${CP} ${.CURDIR}/init${_f} ${_f} ; \
	}
.endfor
