#include "../../includes/minirt.h"

double	**rotation_x(double rad)
{
	double	**res;

	res = identity_matrix();
	res[1][1] = cos(rad);
	res[1][2] = -sin(rad);
	res[2][1] = sin(rad);
	res[2][2] = cos(rad);
	return (res);
}

double	**rotation_y(double rad)
{
	double	**res;

	res = identity_matrix();
	res[0][0] = cos(rad);
	res[0][2] = sin(rad);
	res[2][0] = -sin(rad);
	res[2][2] = cos(rad);
	return (res);
}

double	**rotation_z(double rad)
{
	double	**res;

	res = identity_matrix();
	res[0][0] = cos(rad);
	res[1][0] = sin(rad);
	res[0][1] = -sin(rad);
	res[1][1] = cos(rad);
	return (res);
}