/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_shade_hit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:46 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/10 02:51:18 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_intersections(t_intersection **inter, t_list **xs)
{
	t_list	*temp;

	if ((*inter)->t == 0)
		free(*inter);
	while (*xs)
	{
		temp = (*xs)->next;
		free((*xs)->content);
		free(*xs);
		*xs = temp;
	}
}

t_bool	is_shadowed(t_world w, t_point p)
{
	t_vector		v;
	t_vector		direction;
	double			distance;
	t_list			*xs;
	t_intersection	*inter;

	v = subtract_points(w.l.pos, p);
	distance = magnitude(v);
	direction = normalize(v);
	xs = intersect_world(w, ray(p, direction));
	inter = hit(xs);
	if (inter->t && inter->t < distance)
	{
		free_intersections(&inter, &xs);
		return (TRUE);
	}
	else
	{
		free_intersections(&inter, &xs);
		return (FALSE);
	}
}

t_color	shade_hit(t_world w, t_comps comps)
{
	t_color	c;
	t_bool	shadowed;

	shadowed = is_shadowed(w, comps.over_point);
	c = lighting(comps, w.l, shadowed);
	// if (w.l.ratio == 0)
	// 	return (color(comps.object->material.color.r, comps.object->material.color.g , comps.object->material.color.b));
	return (c);
}
