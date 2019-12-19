/*
 * In this header we don't want to pull in the host xlocale.h (which may not
 * exists as in recent GLibc) but instead just include the basic host
 * locale functions so that xlocale_private.h can function.
 */
#include <locale.h>
