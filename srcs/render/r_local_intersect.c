#include "../../includes/minirt.h"

t_intersect	local_intersect_plane(t_ray r)
{
	t_intersect	inter;

	if (fabs(r.direction.y) < EPSILON)
	{
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		inter.t[2] = 0;
		inter.t[3] = 0;
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
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		inter.t[2] = 0;
		inter.t[3] = 0;
		return (inter);
	}
	return (inter);
}

t_intersect	local_intersect_sphere(t_ray r)
{
	t_intersect	inter;
	t_vector	sphere_to_ray;
	t_tuple		tp1;
	t_tuple		tp2;
	t_point		origin;
	double		a;
	double		b;
	double		c;
	double		d;

	origin = point(0, 0, 0);
	sphere_to_ray = subtract_points(r.origin, origin);
	tp1 = vector_tp(r.direction);
	a = dot(tp1, tp1);
	tp2 = vector_tp(sphere_to_ray);
	b = 2 * dot(tp1, tp2);
	c = dot(tp2, tp2) - 1;
	d = pow(b, 2) - 4 * a * c;
	if (d < 0)
	{
		inter.count = 0;
		inter.t[0] = 0;
		inter.t[1] = 0;
		inter.t[2] = 0;
		inter.t[3] = 0;
		return (inter);
	}
	inter.count = 2;
	inter.t[0] = (-b - sqrt(d)) / (2 * a);
	inter.t[1] = (-b + sqrt(d)) / (2 * a);
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
