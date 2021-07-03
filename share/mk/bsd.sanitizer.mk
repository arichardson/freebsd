.include <bsd.opts.mk>

.include "../../lib/libclang_rt/compiler-rt-vars.mk"
_use_sanitizers=0
# Add the necessary sanitizer flags if requested
.if ${MK_ASAN} == "yes" && (!defined(NO_SHARED) || ${NO_SHARED:tl} == "no")
SANITIZER_CFLAGS+=-fsanitize=address -fPIC
# TODO: remove this once all basic errors have been fixed:
# https://github.com/google/sanitizers/wiki/AddressSanitizer#faq
SANITIZER_CFLAGS+=-fsanitize-recover=address
SANITIZER_LDFLAGS+=-fsanitize=address
_use_sanitizers=1
.endif # ${MK_ASAN} == "yes"

.if ${MK_UBSAN} == "yes" && (!defined(NO_SHARED) || ${NO_SHARED:tl} == "no")
# Unlike the other sanitizers, UBSan could also work for static libraries.
# However, this currently results in linker errors (even with the
# -fsanitize-minimal-runtime flag), so only enable it for dynamically linked
# code for now.
SANITIZER_CFLAGS+=-fsanitize=undefined
SANITIZER_CFLAGS+=-fsanitize-recover=undefined
SANITIZER_LDFLAGS+=-fsanitize=undefined
_use_sanitizers=1
.endif # ${MK_UBSAN} == "yes"

.if !defined(BOOTSTRAPPING) && ${_use_sanitizers} != 0 && \
    ${COMPILER_TYPE} != "clang"
.error "Sanitizer instrumentation currently only supported with clang"
.endif

# For libraries we only instrument the shared and PIE libraries by setting
# SHARED_CFLAGS instead of CFLAGS. We do this since static executables are not
# compatible with the santizers (interceptors do not work).
.if ${_use_sanitizers} != 0
.if target(__<bsd.lib.mk>__)
SHARED_CFLAGS+=	${SANITIZER_CFLAGS}
SOLINKOPTS+=	${SANITIZER_LDFLAGS}
LDFLAGS:=${LDFLAGS:N-Wl,-no-undefined:N-Wl,--no-undefined}
.else
CFLAGS+=	${SANITIZER_CFLAGS}
LDFLAGS+=	${SANITIZER_LDFLAGS}
.endif
.endif # ${_use_sanitizers} != 0
