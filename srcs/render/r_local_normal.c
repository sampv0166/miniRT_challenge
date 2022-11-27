#include "../../includes/minirt.h"

t_vector		local_normal_at_sphere(t_point obj_point, t_point point)
{
	return (subtract_points(obj_point, point));
}

t_vector		local_normal_at_plane()
{
	return (vector(0, 1 ,0));
}

t_vector		local_normal_at_cylinder(t_shape *s, t_point p)
{
	double max;
	double min;
	double dist;
	// // t_shape *cy;

	max = s->height / 2.0;
	min = -1.0 * max;


	// // max = 2.0;
	// // min = 1.0;


	dist = pow(p.x, 2) + pow(p.z, 2);
	if (dist < 1 && p.y >= (max - EPSILON))
		return (vector(0, 1, 0));
	else if (dist < 1 && p.y <= (min + EPSILON))
		return (vector(0, -1, 0));
	else
		return (vector(p.x, 0, p.z));
}
