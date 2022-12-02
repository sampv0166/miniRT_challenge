#include "../../includes/minirt.h"

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
	inter = hit(xs);
	if (inter->t && inter->t < distance)
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
		return (TRUE);
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
		return (FALSE);
	}
}

t_color	shade_hit(t_world w, t_comps comps)
{
	t_color	c;
	t_bool	shadowed;

	shadowed = is_shadowed(w, comps.over_point);
	c = lighting(comps, w.l, shadowed);
	return (c);
}
