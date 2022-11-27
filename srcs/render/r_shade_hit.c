#include "../../includes/minirt.h"

// t_bool	is_shadowed(t_world w, t_point p)
// {
// 	t_vector		v;
// 	double			distance;
// 	t_vector		direction;
// 	t_ray			r;
// 	t_list	*xs;
// 	t_intersection	h;

// 	xs = NULL;
// 	v = subtract_points(w.l.pos, p);
// 	distance = magnitude(v);
// 	direction = normalize(v);
// 	r = ray(p, direction);
// 	xs = intersect_world(w, r);
// 	h = hit(xs);
	 
// 	if (xs)
// 	{
// 		if (h.t && h.t < distance)
// 		{
// 			free(xs);
// 			return TRUE;
// 		}
// 		else
// 		{
// 			free(xs);
// 			return FALSE;
// 		}
// 	}
// 	return (FALSE);
// }

t_bool	is_shadowed(t_world w, t_point p)
{
	t_vector		v;
	double			distance;
	t_vector		direction;
	t_ray			r;
	t_list			*xs;
	t_intersection	*inter;
	t_list			*temp;

	v = subtract_points(w.l.pos, p);
	distance = magnitude(v);
	direction = normalize(v);
	r = ray(p, direction);
	xs = intersect_world(w, r);
	inter  = hit(xs);

	if (inter->t && inter->t < distance)
	{
		// free(inter);
		if (inter->t == 0)
		{
			free(inter);
		}
		while (xs)
		{
			temp = xs->next;
			free(xs->content);
			free(xs);
			xs = temp;
		}
		return TRUE;
	}
	else
	{
		if (inter->t == 0)
		{
			free(inter);
		}
		while (xs)
		{
			temp = xs->next;
			free(xs->content);
			free(xs);
			xs = temp;
		}
		// free(inter);
		return FALSE;
	}
}

// t_vector	reflect(t_vector vec, t_vector normal)
// {
// 	t_vector	ret;
// 	double		d;

// 	d = 2 * dot(vector_tp(vec), vector_tp(normal));
// 	normal.x = normal.x * d;
// 	normal.y = normal.y * d;
// 	normal.z = normal.z * d;
// 	ret.x = vec.x - normal.x;
// 	ret.y = vec.y - normal.y;
// 	ret.z = vec.z - normal.z;
// 	return (ret);
// }

// t_color	lighting(t_material m, t_light l, t_point pos,
// 	t_vector eyev, t_vector normalv, t_bool in_shadow)
// {
// 	t_point		effective_color;
// 	t_vector	lightv;
// 	t_vector	reflectv;
// 	t_color		ambient;
// 	t_color		diffuse;
// 	t_color		specular;
// 	t_color		ret;
// 	double		light_dot_normal;
// 	double		reflect_dot_eye;
// 	double		factor;
// 	t_point		p;
// 	t_tuple		tp1;
// 	t_tuple		tp2;
// 	t_tuple		tp3;
// 	effective_color.x = m.color.r * l.color.r;
// 	effective_color.y = m.color.g * l.color.g;
// 	effective_color.z = m.color.b * l.color.b;


// 	p = point(l.pos.x, l.pos.y, l.pos.z);
// 	lightv = normalize(subtract_points(p, pos));

// 	tp1 = multiply(point_tp(effective_color), m.ambient);

	
// 	ambient = color(tp1.x, tp1.y, tp1.z);
// 	light_dot_normal = dot(vector_tp(lightv), vector_tp(normalv));
// 	if (light_dot_normal < 0 || in_shadow)
// 	{
// 		diffuse = color(0, 0, 0);
// 		specular = color(0, 0, 0);
// 	}
// 	else
// 	{
// 		tp2 = multiply(point_tp(effective_color), m.diffuse);
// 		tp3 = multiply(tp2, light_dot_normal);
// 		diffuse = color(tp3.x, tp3.y, tp3.z);
// 		reflectv = reflect(negate_vector(lightv), normalv);
// 		reflect_dot_eye = dot(vector_tp(reflectv), vector_tp(eyev));
// 		if (reflect_dot_eye <= 0)
// 			specular = color(0, 0, 0);
// 		else
// 		{
// 			factor = pow(reflect_dot_eye, m.shininess);
// 			specular.r = l.color.r * m.specular * factor;
// 			specular.g = l.color.g * m.specular * factor;
// 			specular.b = l.color.b * m.specular * factor;
// 		}
// 	}
// 	ret.r = ambient.r + diffuse.r + specular.r;
// 	ret.g = ambient.g + diffuse.g + specular.g;
// 	ret.b = ambient.b + diffuse.b + specular.b;


// 	return (ret);
// }

t_color	shade_hit(t_world w, t_comps comps)
{
	t_color	c;
	t_bool	shadowed;

	shadowed = is_shadowed(w, comps.over_point);
	c = lighting(comps, w.l, shadowed);
	return (c);
}