/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_cyl_cap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:31:48 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 14:32:41 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_cap(t_ray ray, double t)
{
	double	x;
	double	z;

	x = ray.origin.x + t * ray.direction.x;
	z = ray.origin.z + t * ray.direction.z;
	if ((pow(x, 2) + pow(z, 2)) <= 1)
		return (1);
	return (0);
}

t_intersect	intersect_caps(t_shape *cy, t_ray ray, t_intersect *i, \
			t_list **intersections_lst)
{
	double			min;
	double			max;

	max = cy->height / 2.0;
	min = -1.0 * max;
	i->t[2] = (min - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, i->t[2]))
		create_intersection(intersections_lst, i->t[2], cy);
	else
		i->t[2] = 0;
	i->t[3] = (max - ray.origin.y) / ray.direction.y;
	if (check_cap(ray, i->t[3]))
		create_intersection(intersections_lst, i->t[3], cy);
	else
		i->t[3] = 0;
	return (*i);
}
