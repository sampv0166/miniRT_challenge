#include "../../includes/minirt.h"

t_intersect	local_intersect_plane(t_ray r)
{
	t_intersect	inter;

	if (fabs(r.direction.y) < EPSILON)
	{
		init_intersect(&inter);
		return (inter);
	}
	inter.count = 2;
	inter.t[0] = -1 * r.origin.y / r.direction.y ;
	inter.t[1] = 0;
	inter.t[2] = 0;
	inter.t[3] = 0;
	if (inter.t[0] > 0)
		return (inter);
	else
	{
		init_intersect(&inter);
		return (inter);
	}
	return (inter);
}

t_intersect	local_intersect_sphere(t_ray r)
{
	t_intersect	inter;
	t_vector	sphere_to_ray;
	t_tuple		tp[2];
	t_point		origin;
	double		calc[4];

	origin = point(0, 0, 0);
	sphere_to_ray = subtract_points(r.origin, origin);
	tp[0] = vector_tp(r.direction);
	tp[1] = vector_tp(sphere_to_ray);
	calc[0] = dot(tp[0], tp[0]);
	calc[1] = 2 * dot(tp[0], tp[1]);
	calc[2] = dot(tp[1], tp[1]) - 1;
	calc[3] = pow(calc[1], 2) - 4 * calc[0] * calc[2];
	if (calc[3] < 0)
	{
		init_intersect(&inter);
		return (inter);
	}
	inter.count = 2;
	inter.t[0] = (-calc[1] - sqrt(calc[3])) / (2 * calc[0]);
	inter.t[1] = (-calc[1] + sqrt(calc[3])) / (2 * calc[0]);
	inter.t[2] = 0;
	inter.t[3] = 0;
	return (inter);
}

t_intersect	local_intersect_cylinder(t_shape *s, t_ray ray)
{
	double		calc;
	t_intersect	inter1;
	double		min;
	double		max;

	max = s->height / 2.0;
	min = -1.0 * max;
	init_intersect(&inter1);
	calc = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	if (fabs(calc) < EPSILON)
		return (inter1);
	set_intersect(&inter1, ray, min, max);
	if (fabs(ray.direction.y) < EPSILON)
		return (inter1);
	return (intersect_caps(s, ray, &inter1));
}
