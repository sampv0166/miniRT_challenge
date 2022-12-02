#include "../../includes/minirt.h"

t_vector	local_normal_at_sphere(t_point obj_point, t_point point)
{
	return (subtract_points(obj_point, point));
}

t_vector	local_normal_at_plane(void)
{
	return (vector(0, 1, 0));
}

t_vector	local_normal_at_cylinder(double h, t_point pnt)
{
	double	max;
	double	min;
	double	dist;

	max = h / 2.0;
	min = -1.0 * max;
	dist = pow(pnt.x, 2) + pow(pnt.z, 2);
	if (dist < 1 && pnt.y >= max - EPSILON)
		return (vector(0, 1, 0));
	else if (dist < 1 && pnt.y <= min + EPSILON)
		return (vector(0, -1, 0));
	else
		return (vector(pnt.x, 0, pnt.z));
}
