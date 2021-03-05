#include <math.h>

float remainderf(float x, float y)
{
	int q;
	return remquof(x, y, &q);
}

__weak_reference(remainderf, dremf);
