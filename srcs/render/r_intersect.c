#include "../../includes/minirt.h"

t_intersect	intersect(t_shape *s, t_ray r)
{
	s->ray_in_obj_space = transform(r, s->inverse);
	if (!ft_strncmp(s->shape_name, "sp", 2))
		return (local_intersect_sphere(s->ray_in_obj_space));
	else if (!ft_strncmp(s->shape_name, "pl", 2))
		return (local_intersect_plane(s->ray_in_obj_space));
	else if (!ft_strncmp(s->shape_name, "cy", 2))
		return (local_intersect_cylinder(s, s->ray_in_obj_space));
	return (local_intersect_sphere(s->ray_in_obj_space));
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
	t_intersect		inter;
	t_shape			*temp_shape;
	t_intersection	**intersection;

	intersections_list = NULL;
	shapes = w.shapes;
	intersection = malloc (sizeof (t_intersection) * 4);
	while (shapes)
	{	
		temp_shape = (t_shape *) shapes->content;
		inter = intersect(temp_shape, r);
		if (inter.t[0] + inter.t[1] + inter.t[2] + inter.t[3] > 0)
		{
			add_intersections(intersection, temp_shape, inter);
			create_intersections_list(intersection, &intersections_list);
		}
		shapes = shapes->next;
	}
	free(intersection);
	return (intersections_list);
}
