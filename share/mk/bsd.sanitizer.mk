.include <bsd.opts.mk>

#.info MK_MSAN=${MK_MSAN} MK_ASAN=${MK_ASAN} MK_UBSAN=${MK_UBSAN}
#.info NO_SHARED=${NO_SHARED} NO_PIC=${NO_PIC} MK_PIE=${MK_PIE}

# Add the necessary sanitizer flags if requested
.if ${MK_ASAN} == "yes" && (!defined(NO_SHARED) || ${NO_SHARED:tl} == "no")
DYNAMIC_SANITIZER_CFLAGS+=-fsanitize=address -fPIC
# TODO: remove this once all basic errors have been fixed:
# https://github.com/google/sanitizers/wiki/AddressSanitizer#faq
DYNAMIC_SANITIZER_CFLAGS+=-fsanitize-recover=address
DYNAMIC_SANITIZER_LDFLAGS+=-fsanitize=address
.if ${LDFLAGS:M-Wl,--no-undefined}
.if 0
# Work around -Wl,--no-undefined errors for shared libraries by linking against
# the share libasan.so
SOLINKOPTS+=-shared-libasan
SOLINKOPTS+=	-Wl,--enable-new-dtags
SOLINKOPTS+=	-Wl,-rpath,/usr/lib/clang/11.0.0/lib/freebsd
.else
LDFLAGS:=${LDFLAGS:N-Wl,--no-undefined}
.endif
.endif
.endif # ${MK_ASAN} == "yes"

.if ${MK_UBSAN} == "yes" && (!defined(NO_SHARED) || ${NO_SHARED:tl} == "no")
# Unlike the other sanitizers, UBSan could also work for static libraries.
# However, this currently results in linker errors (even with the
# -fsanitize-minimal-runtime flag), so only enable it for dynamically linked
# code for now.
DYNAMIC_SANITIZER_CFLAGS+=-fsanitize=undefined
DYNAMIC_SANITIZER_CFLAGS+=-fsanitize-recover=undefined
DYNAMIC_SANITIZER_LDFLAGS+=-fsanitize=undefined
.endif # ${MK_UBSAN} == "yes"

.if ${MK_MSAN} == "yes" && (!defined(NO_SHARED) || ${NO_SHARED:tl} == "no")
# Note: MSAN does not work when linking libc statically.
.if ${MK_ASAN} == "yes"
.error "ASan and MSan are mutally exclusive"
.endif
# For more useful backtraces add -fsanitize-memory-track-origins=2
# Note: MSan flags are not added to SANITIZER_CFLAGS by default since we need to build
# separate libraries and explicitly add it in bsd.prog.mk
# The separate MSAN_* variables exist so that certain directories can override
# them (e.g. if they want to add -fsanitize-memory-track-origins).
MSAN_CFLAGS?=-fsanitize=memory -fPIC
MSAN_CXXFLAGS?=-fsanitize=memory -fPIC
MSAN_LDFLAGS?=-fsanitize=memory

.if defined(NO_MSAN) && !defined(BOOTSTRAPPING) && !defined(_BUILDING_RTLD)
# Programs that opt-out of MSAN instrumentation need to link a non-msan libc
MSAN_LDFLAGS+=-nodefaultlibs -lc_nomsan -static
# Can't use -pie since this will break
LDFLAGS:=${LDFLAGS:N-pie}
.if defined(PROG_CXX)
MSAN_LDFLAGS+=-lc++_nomsan -lcxxrt_nomsan -lgcc_eh_nomsan
.endif
.endif
DYNAMIC_SANITIZER_LDFLAGS+=${MSAN_LDFLAGS}
DYNAMIC_SANITIZER_CFLAGS+=${MSAN_SANITIZER_CFLAGS}
.endif # ${MK_MSAN} == "yes"

# Ensure that we can find the right sanitizer runtime libraries in buildworld
# However, we mustn't override -resource-dir= for the bootstrap phase, since
# we need to link the host system sanitizer library there.
.if defined(SRCTOP) && !defined(BOOTSTRAPPING) && \
    (${MK_ASAN} == "yes" || ${MK_MSAN} == "yes" || ${MK_UBSAN} == "yes")
.if ${COMPILER_TYPE} == "clang"
# FIXME: should share the version number with clang_rt/Makefile, etc.
# Note: Clang ignores -L flags for the sanitizer runtimes so we need to pass
# the -resource-dir= flag instead.
DYNAMIC_SANITIZER_LDFLAGS+=	-resource-dir=${LIBDESTDIR}${LIBDIR_BASE}/clang/11.0.0/
.else
.error "Sanitizer instrumentation currently only supported with clang"
.endif
.endif # defined(SRCTOP) && !defined(BOOTSTRAPPING) && USING_A_SANITIZER

# For libraries we only instrument shared libs by setting SHARED_CFLAGS instead
# of CFLAGS since static executables are not compatible with santizers (because
# interceptors do not work)
.if !defined(LIB)
CFLAGS+=	${DYNAMIC_SANITIZER_CFLAGS}
LDFLAGS+=	${DYNAMIC_SANITIZER_LDFLAGS}
.else
SHARED_CFLAGS+=	${DYNAMIC_SANITIZER_CFLAGS}
SOLINKOPTS+=	${DYNAMIC_SANITIZER_LDFLAGS}
.endif
