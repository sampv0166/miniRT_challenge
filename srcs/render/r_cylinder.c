/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:56 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 14:31:28 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_intersect(t_intersect *inter1)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		(*inter1).t[i] = 0;
		i++;
	}
	(*inter1).count = 0;
}

void	create_intersection(t_list **intersections_list, double t, \
	t_shape *shape)
{
	t_intersection	*inter;

	inter = malloc (sizeof (t_intersection));
	inter->object = shape;
	inter->t = t;
	inter->count = 1;
	if (*intersections_list == NULL)
		*intersections_list = ft_lstnew(inter);
	else
		ft_lstadd_back(intersections_list, ft_lstnew(inter));
}

void	check_intersect(t_intersect *inter1, \
		t_ray ray, t_list **intersections_list, t_shape *s)
{
	double		y0_y1[2];
	double		temp;

	if ((*inter1).t[0] > (*inter1).t[1])
	{
		temp = (*inter1).t[0];
		(*inter1).t[0] = (*inter1).t[1];
		(*inter1).t[1] = temp;
	}
	y0_y1[0] = ray.origin.y + ((*inter1).t[0] * ray.direction.y);
	y0_y1[1] = ray.origin.y + ((*inter1).t[1] * ray.direction.y);
	if (s->min < y0_y1[0] && y0_y1[0] < s->max)
	{
		if (inter1->t[0] > EPSILON)
			create_intersection(intersections_list, inter1->t[0], s);
	}
	else
		(*inter1).t[0] = 0;
	if (s->min < y0_y1[1] && y0_y1[1] < s->max)
	{
		if (inter1->t[0] > EPSILON)
			create_intersection(intersections_list, inter1->t[1], s);
	}
	else
		(*inter1).t[1] = 0;
}

void	set_intersect(t_intersect *inter1, t_ray ray, \
		t_list **intersections_list, t_shape *s)
{
	double	a;
	double	b;
	double	c;
	double	disc;

	a = pow(ray.direction.x, 2) + pow(ray.direction.z, 2);
	b = (2 * ray.origin.x * ray.direction.x)
		+ (2 * ray.origin.z * ray.direction.z);
	c = (pow(ray.origin.x, 2) + pow(ray.origin.z, 2)) - 1.0;
	disc = pow(b, 2) - (4 * a * c);
	(*inter1).t[0] = (((-1 * b) - sqrt(disc)) / (2 * a));
	(*inter1).t[1] = (((-1 * b) + sqrt(disc)) / (2 * a));
	if (disc >= 0 && (double_equal(a, 0) == 0))
		check_intersect(inter1, ray, intersections_list, s);
	else
	{
		(*inter1).t[0] = 0;
		(*inter1).t[1] = 0;
	}
}
