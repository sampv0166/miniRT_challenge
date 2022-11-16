#include "../../includes/minirt.h"

t_point	position(t_ray r, float num)
{
	t_tuple	multi;
	t_tuple	res;
	t_point	p;

	multi = multiply(vector_tp(r.direction), num);
	res = add(point_tp(r.origin), multi);
	p = point(res.x, res.y, res.z);
	return (p);
}

t_vector	normal_at(t_shape *s, t_point p)
{
	t_vector	obj_normal;
	t_vector	world_normal;
	t_point		point;
	t_point		obj_point;
	t_tuple		tp1;
	t_tuple		tp2;
	t_tuple		tp3;
	t_tuple		tp4;
	double		**invrs;
	double		**trnspose;

	tp1 = point_tp(p);
		// 

	invrs = inverse(s->transform, 4);
	tp2 = matrix_multi_tp(invrs, tp1);
	obj_point.x = tp2.x;
	obj_point.y = tp2.y;
	obj_point.z = tp2.z;
	point.x = 0;
	point.y = 0;
	point.z = 0;
	if (!ft_strncmp(s->shape_name, "sp", 2))
		obj_normal = local_normal_at_sphere(obj_point, point);
	if (!ft_strncmp(s->shape_name, "pl", 2))
		obj_normal = local_normal_at_plane(obj_point, point);
	if (!ft_strncmp(s->shape_name, "cy", 2))
		obj_normal = local_normal_at_cylinder(s->shape,obj_point);	
	tp3 = vector_tp(obj_normal);

	trnspose = transpose(invrs);
	tp4 = matrix_multi_tp(trnspose , tp3);
	world_normal.x = tp4.x;
	world_normal.y = tp4.y;
	world_normal.z = tp4.z;

	free_2d_array(invrs,4 );
	free_2d_array(trnspose,4 );
	return (normalize(world_normal));
}

t_comps	prepare_computations(t_intersection i, t_ray r)
{
	t_comps	comps;

	comps.t = i.t;
	comps.object = i.object;
	comps.point = position(r, comps.t);
	comps.eyev = negate_vector(r.direction);
	comps.normalv = normal_at(comps.object, comps.point);
	comps.over_point.x = comps.point.x + comps.normalv.x * EPSILON;
	comps.over_point.y = comps.point.y + comps.normalv.y * EPSILON;
	comps.over_point.z = comps.point.z + comps.normalv.z * EPSILON;
	if (dot(vector_tp(comps.normalv), vector_tp(comps.eyev)) < 0)
	{
		comps.inside = TRUE;
		comps.normalv = negate_vector(comps.normalv);
	}
	else
		comps.inside = FALSE;
	return (comps);
}