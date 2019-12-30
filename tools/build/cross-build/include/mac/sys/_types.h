#pragma once
#include_next <sys/_types.h>

/*
 * Bootstrapping localedef needs a __ct_rune_t typedef, but on macos only
 * __darwin_ct_rune_t exists.
 */
typedef __darwin_ct_rune_t __ct_rune_t;
