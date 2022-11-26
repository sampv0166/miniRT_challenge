#include "../../includes/minirt.h"

t_vector		local_normal_at_sphere(t_point obj_point, t_point point)
{
	return (subtract_points(obj_point, point));
}

t_vector		local_normal_at_plane()
{
	return (vector(0, 1 ,0));
}

t_vector		local_normal_at_cylinder(t_shape *shape,  t_point pnt)
{
	(void ) shape;
	// double max;
	// double min;
	// // t_shape *cy;

	// max = shape->height / 2.0;
	// min = -1.0 * max;


	// // max = 2.0;
	// // min = 1.0;

	// double dist;

	// dist = pow(pnt.x, 2) + pow(pnt.z, 2);
	// if (dist < 1 && pnt.y >= max - EPSILON)
	// 	return vector(0, 1, 0);
	// else if (dist < 1 && pnt.y <= min + EPSILON)
	// 	return vector(0, -1, 0);
	// else
	return (vector(pnt.x, 0 ,pnt.z));
}
