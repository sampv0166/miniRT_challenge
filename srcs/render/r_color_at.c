/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_color_at.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:48 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:27:48 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	transform(t_ray r, double **m)
{
	t_ray		ret;
	t_tuple		tp[2];
	t_tuple		multi[2];
	t_point		p;
	t_vector	vec;

	tp[0] = point_tp(r.origin);
	multi[0] = matrix_multi_tp(m, tp[0]);
	tp[1] = vector_tp(r.direction);
	multi[1] = matrix_multi_tp(m, tp[1]);
	p = point(multi[0].x, multi[0].y, multi[0].z);
	vec = vector(multi[1].x, multi[1].y, multi[1].z);
	ret.origin = p;
	ret.direction = vec;
	return (ret);
}

static void	free_intersections(t_list **xs)
{
	t_list	*temp;

	while (*xs)
	{
		temp = (*xs)->next;
		free((*xs)->content);
		free(*xs);
		*xs = temp;
	}
}

t_color		color_at(t_world w, t_ray r)
{
	t_list			*intersections_list;
	t_comps			comps;
	t_intersection	*inter;

	intersections_list = NULL;
	
	intersections_list = intersect_world(w, r);
	
	inter = hit(intersections_list);
	if (inter->t <= EPSILON)
	{
		free_intersections(&intersections_list);
		if (inter->t == 0)
		{
			free(inter);
		}
		return (color(0, 0, 0));
	}
	comps = prepare_computations(inter, r);
	if (inter->count == 0)
	{
		free(inter);
	}
	free_intersections(&intersections_list);
	
	return (shade_hit(w, comps));
}
