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

t_intersect	intersect(t_shape *s, t_ray r)
{
	double	**invrs;

	invrs = inverse(s->transform, 4);
	s->ray_in_obj_space = transform(r, invrs);
	free_2d_array(invrs, 4);
	if (!ft_strncmp(s->shape_name, "sp", 2))
		return (local_intersect_sphere(s->ray_in_obj_space));
	else if (!ft_strncmp(s->shape_name, "pl", 2))
		return (local_intersect_plane(s->ray_in_obj_space));
	else if (!ft_strncmp(s->shape_name, "cy",2))
		return (local_intersect_cylinder(s->height, s->ray_in_obj_space));
	return (local_intersect_sphere(s->ray_in_obj_space));

}

t_list	*intersect_world(t_world w, t_ray r) 
{
	static int		i;
	t_list			*intersections_list;
	t_list			*shapes;
	t_intersect		inter;
	t_shape			*temp_shape;
	int				first_check;
	t_intersection	*intersection1;
	t_intersection	*intersection2;

	first_check = 0;
	intersections_list = NULL;
	shapes = w.shapes;
	i++;
	while (shapes)
	{	
		temp_shape = (t_shape *) shapes->content;
		inter = intersect(temp_shape, r);
		if (inter.count > 0)
		{
			intersection1 = malloc (sizeof (t_intersection));
			intersection2 = malloc (sizeof (t_intersection));
			intersection1->object = temp_shape;
			intersection1->t = inter.t[0];
			intersection1->count = 1;

			intersection2->object = temp_shape;
			intersection2->t = inter.t[1];
			intersection2->count = 1;
			if (first_check == 0)
			{
				intersections_list = ft_lstnew(intersection1);
				ft_lstadd_back(&intersections_list, ft_lstnew(intersection2));
				first_check = 1;
			}
			else
			{
				ft_lstadd_back(&intersections_list, ft_lstnew(intersection1));
				ft_lstadd_back(&intersections_list, ft_lstnew(intersection2));
			}
		}
		shapes = shapes->next;
	}
	return (intersections_list);
}

t_color	color_at(t_world w, t_ray r)
{
	t_list			*intersections_list;
	t_comps			comps;
	t_intersection	*inter;
	t_list			*temp;

	intersections_list = intersect_world(w, r);
	inter = hit(intersections_list);
	if (inter->count == 0)
	{
		free(inter);
		while (intersections_list)
		{
			temp = intersections_list->next;
			free(intersections_list->content);
			free(intersections_list);
			intersections_list = temp;
		}
		return (color(0, 0, 0));
	}

	comps = prepare_computations(inter, r);
	while (intersections_list)
	{
		temp = intersections_list->next;
		free(intersections_list->content);
		free(intersections_list);
		intersections_list = temp;
	}
	return (shade_hit(w, comps));
}
