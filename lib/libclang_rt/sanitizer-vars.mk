CLANG_SUBDIR=clang/11.0.1
CLANGDIR=	/usr/lib/${CLANG_SUBDIR}
SANITIZER_LIBDIR=		${CLANGDIR}/lib/freebsd

.if ${COMPILER_TYPE} == "clang"
# The only way to set the path to the sanitizer libraries with clang is to
# override the resource directory
# Note: lib/freebsd is automatically appended to the resource-dir value.
SANITIZER_LDFLAGS=	-resource-dir=${SYSROOT}${CLANGDIR}
# Also set RPATH to ensure that the dynamically linked runtime libs are found.
SANITIZER_LDFLAGS+=	-Wl,--enable-new-dtags
SANITIZER_LDFLAGS+=	-Wl,-rpath,${SANITIZER_LIBDIR}
.info SANITIZER_LDFLAGS=${SANITIZER_LDFLAGS}
.else
.error "Unknown link flags for -fsanitize=... COMPILER_TYPE=${COMPILER_TYPE}"
.endif
