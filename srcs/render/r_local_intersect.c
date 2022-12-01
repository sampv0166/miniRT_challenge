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

static int	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((pow(x, 2) + pow(z, 2)) <= 1)
		return (1);
	return (0);
}

t_intersect	intersect_caps(t_shape *cy, t_ray ray, t_intersect *i)
{
	double			min;
	double			max;

	max = cy->height / 2.0;
	min = -1.0 * max;
	i->t[2] = (min - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, i->t[2]))
		i->count++;
	else
		i->t[2] = 0;
	i->t[3] = (max - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, i->t[3]))
		i->count++;
	else
		i->t[3] = 0;
	return (*i);
}

t_intersect local_intersect_cylinder(t_shape *s, t_ray ray)
{
	double		a;
	double		b;
	double		c;
	double		disc;
	t_intersect	inter1;
	double		min;
	double		max;
	double		y0_y1[2];
	double		temp;

	max = s->height / 2.0;
	min = -1.0 * max;
	inter1.t[0] = 0;
	inter1.t[1] = 0;
	inter1.t[2] = 0;
	inter1.t[3] = 0;
	inter1.count = 0;
	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = (2 * ray.origin.x * ray.direction.x)
		+ (2 * ray.origin.z * ray.direction.z);
	c = (pow(ray.origin.x, 2) + pow(ray.origin.z, 2)) - 1.0;
	disc = pow(b, 2) - (4 * a * c);
	if (fabs(a) < EPSILON)
		return (inter1);
	inter1.t[0] = (((-1 * b) - sqrt(disc)) / (2 * a));
	inter1.t[1] = (((-1 * b) + sqrt(disc)) / (2 * a));
	if (disc >= 0 && (double_equal(a, 0) == 0))
	{
		if (inter1.t[0] > inter1.t[1])
		{
			temp = inter1.t[0];
			inter1.t[0] = inter1.t[1];
			inter1.t[1] = temp;
		}
		y0_y1[0] = ray.origin.y + (inter1.t[0] * ray.direction.y);
		y0_y1[1] = ray.origin.y + (inter1.t[1] * ray.direction.y);
		if (min < y0_y1[0] && y0_y1[0] < max)
			inter1.count++;
		else
			inter1.t[0] = 0;
		if (min < y0_y1[1] && y0_y1[1] < max)
			inter1.count++;
		else
			inter1.t[1] = 0;
	}
	else
	{
		inter1.t[0] = 0;
		inter1.t[1] = 0;
	}
	if (fabs(ray.direction.y) < EPSILON)
		return (inter1);
	return (intersect_caps(s, ray, &inter1));
}
