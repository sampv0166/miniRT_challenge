#include "../../includes/minirt.h"

void	local_intersect_plane(t_shape *s, t_list **intersections_list)
{
	t_intersect	inter;

	if (fabs(s->ray_in_obj_space.direction.y) < EPSILON)
	{
		init_intersect(&inter);
		return ;
	}
	inter.count = 1;
	inter.t[0] = -1 * s->ray_in_obj_space.origin.y / s->ray_in_obj_space.direction.y ;

	if (inter.t[0] > EPSILON)
		create_intersection(intersections_list , inter.t[0],s);
	else
	{
		return ;
	}
	return ;
}

void	local_intersect_sphere(t_shape *s, t_list **intersections_list)
{
	t_intersect	inter;
	t_vector	sphere_to_ray;
	t_tuple		tp[2];
	t_point		origin;
	double		calc[4];

	origin = point(0, 0, 0);
	sphere_to_ray = subtract_points(s->ray_in_obj_space.origin, origin);
	tp[0] = vector_tp(s->ray_in_obj_space.direction);
	tp[1] = vector_tp(sphere_to_ray);
	calc[0] = dot(tp[0], tp[0]);
	calc[1] = 2 * dot(tp[0], tp[1]);
	calc[2] = dot(tp[1], tp[1]) - 1;
	calc[3] = pow(calc[1], 2) - 4 * calc[0] * calc[2];
	if (calc[3] < 0)
		return ;
	inter.count = 2;
	inter.t[0] = (-calc[1] - sqrt(calc[3])) / (2 * calc[0]);
	inter.t[1] = (-calc[1] + sqrt(calc[3])) / (2 * calc[0]);
	create_intersection(intersections_list, inter.t[0], s);
	create_intersection(intersections_list, inter.t[1], s);
}

t_intersect	local_intersect_cylinder(t_shape *s, t_ray ray,  t_list **intersections_list)
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
	set_intersect(&inter1, ray, min, max, intersections_list, s);
	if (fabs(ray.direction.y) < EPSILON)
		return (inter1);
	return (intersect_caps(s, ray, &inter1, intersections_list));
}
