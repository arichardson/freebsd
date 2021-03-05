#include <math.h>

double remainder(double x, double y)
{
	int q;
	return remquo(x, y, &q);
}

#if LDBL_MANT_DIG == 53
__weak_reference(remainder, remainderl);
__weak_reference(remainder, drem);
#endif
