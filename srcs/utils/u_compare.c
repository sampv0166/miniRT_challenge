#include "../../includes/minirt.h"

int	double_equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}
