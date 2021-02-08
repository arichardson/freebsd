#include <sys/cdefs.h>
__FBSDID("$FreeBSD$");

#include "namespace.h"
#include "libc_private.h"

#include <port_before.h>
#ifdef DO_PTHREADS
#include <pthread.h>
#ifdef _LIBC
#include <pthread_np.h>
#endif
#endif
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <resolv_mt.h>
#include "un-namespace.h"

#ifdef DO_PTHREADS
static pthread_key_t	key;
static pthread_once_t	key_once = PTHREAD_ONCE_INIT;

static int		__res_init_ctx(void);
static void		__res_destroy_ctx(void *);

#if defined(sun) && !defined(__GNUC__)
#pragma init	(_mtctxres_init)
#endif
#endif

static mtctxres_t	sharedctx;

#ifdef DO_PTHREADS
/*
 * Initialize the TSD key. By doing this at library load time, we're
 * implicitly running without interference from other threads, so there's
 * no need for locking.
 */
static void
_mtctxres_init(void) {
	_pthread_key_create(&key, __res_destroy_ctx);
}
#endif

#ifndef _LIBC
/*
 * To support binaries that used the private MT-safe interface in
 * Solaris 8, we still need to provide the __res_enable_mt()
 * and __res_disable_mt() entry points. They're do-nothing routines.
 */
int
__res_enable_mt(void) {
	return (-1);
}

int
__res_disable_mt(void) {
	return (0);
}
#endif

#ifdef DO_PTHREADS
static int
__res_init_ctx(void) {

	mtctxres_t	*mt;
	int		ret;


	if (_pthread_getspecific(key) != 0) {
		/* Already exists */
		return (0);
	}

	if ((mt = malloc(sizeof(mtctxres_t))) == NULL) {
		errno = ENOMEM;
		return (-1);
	}

	memset(mt, 0, sizeof (mtctxres_t));

	if ((ret = _pthread_setspecific(key, mt)) != 0) {
		free(mt);
		errno = ret;
		return (-1);
	}

	return (0);
}

static void
__res_destroy_ctx(void *value) {

	free(value);
}
#endif

mtctxres_t *
___mtctxres(void) {
#ifdef DO_PTHREADS
	mtctxres_t	*mt;

#ifdef _LIBC
	if (_pthread_main_np() != 0)
		return (&sharedctx);
#endif

	_pthread_once(&key_once, _mtctxres_init);
	/*
	 * If we have already been called in this thread return the existing
	 * context.  Otherwise recreat a new context and return it.  If
	 * that fails return a global context.
	 */
	if (((mt = _pthread_getspecific(key)) != NULL) ||
	    (__res_init_ctx() == 0 &&
	     (mt = _pthread_getspecific(key)) != NULL)) {
		return (mt);
	}
#endif
	return (&sharedctx);
}
