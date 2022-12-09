/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_intersect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:09 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/10 02:48:27 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	intersect(t_shape *s, t_ray r, t_list **intersections_list)
{
	s->ray_in_obj_space = transform(r, s->inverse);
	if (!ft_strncmp(s->shape_name, "sp", 2))
		local_intersect_sphere(s, intersections_list);
	else if (!ft_strncmp(s->shape_name, "pl", 2))
		return (local_intersect_plane(s, intersections_list));
	else if (!ft_strncmp(s->shape_name, "cy", 2))
		local_intersect_cylinder(s, s->ray_in_obj_space, intersections_list);
}

void	add_intersections(t_intersection **intersection,
	t_shape *temp, t_intersect inter)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		intersection[i] = malloc (sizeof (t_intersection));
		intersection[i]->object = temp;
		intersection[i]->t = inter.t[i];
		intersection[i]->count = 1;
		i++;
	}
}

void	create_intersections_list(t_intersection **intersection,
	t_list **intersections_list)
{
	static int	first_check;

	if (!first_check)
		first_check = 0;
	if (first_check == 0)
	{
		*intersections_list = ft_lstnew(intersection[0]);
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[1]));
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[2]));
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[3]));
		first_check = 1;
	}
	else
	{
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[0]));
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[1]));
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[2]));
		ft_lstadd_back(intersections_list, ft_lstnew(intersection[3]));
	}
}

t_list	*intersect_world(t_world w, t_ray r)
{
	t_list			*intersections_list;
	t_list			*shapes;
	t_shape			*temp_shape;

	shapes = w.shapes;
	intersections_list = NULL;
	while (shapes)
	{	
		temp_shape = (t_shape *) shapes->content;
		intersect (temp_shape, r, &intersections_list);
		shapes = shapes->next;
	}
	return (intersections_list);
}
