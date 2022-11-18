#include "../../includes/minirt.h"

t_ray	transform(t_ray r, double **m)
{
	t_ray		ret;
	t_tuple		tp1;
	t_tuple		tp2;
	t_tuple		multi1;
	t_tuple		multi2;
	t_point		p;
	t_vector	vec;

	tp1 = point_tp(r.origin);
	multi1 = matrix_multi_tp(m, tp1);
	tp2 = vector_tp(r.direction);
	multi2 = matrix_multi_tp(m, tp2);
	p = point(multi1.x, multi1.y, multi1.z);
	vec = vector(multi2.x, multi2.y, multi2.z);
	ret.origin = p;
	ret.direction = vec;
	return (ret);
}

t_intersect	intersect(t_shape s, t_ray r)
{
	double **invrs;

	invrs = inverse(s.transform, 4);
	s.ray_in_obj_space = transform(r, invrs);
	free_2d_array(invrs, 4);
	if (!ft_strncmp(s.shape_name, "sp", 2))
		return (local_intersect_sphere(s.ray_in_obj_space));
	else if(!ft_strncmp(s.shape_name, "pl", 2))
		return(local_intersect_plane(s.ray_in_obj_space));
	else if (!ft_strncmp(s.shape_name, "cy",2))
		return(local_intersect_cylinder( &s , s.ray_in_obj_space));
	return (local_intersect_sphere(s.ray_in_obj_space));		
}

t_list	*intersect_world(t_world w, t_ray r)
{
	t_list *xs;
	t_list *shapes;

	t_intersect inter;
	t_intersection *intersection1;
	t_intersection *intersection2;
	int i;
	int count;

	i = 0;
	count = 0;
	xs = NULL;
	t_shape *s;
	shapes = w.shapes;

	while (shapes)
	{
		s = (t_shape *) shapes->content;
		inter = intersect_sphere(s, r);
		if (inter.count > 0)
		{
			intersection1 = malloc (sizeof (t_intersection));
			intersection2 = malloc (sizeof (t_intersection));

			intersection1->object = s;
			intersection1->t = inter.t[0];

			intersection2->object = s;
			intersection2->t = inter.t[1];
			if (i == 0)
			{
				xs = ft_lstnew(intersection1);
				ft_lstadd_back(&xs, ft_lstnew(intersection2));
			}
			else
			{
				ft_lstadd_back(&xs, ft_lstnew(intersection1));
				ft_lstadd_back(&xs, ft_lstnew(intersection2));
			}
			// intersection1 = (t_intersection *) xs->content;
			// printf("\n%f\n",intersection1->t);
			// intersection1 = (t_intersection *) xs->next->content;
			// printf("\n%f\n",intersection1->t);
			// 	printf("\n%f\n",intersection1->t);
			count = count + inter.count;
		}		shapes = shapes->next;		i++;
	}

	t_list *lst;
	lst = xs;

	while (lst)
	{
		intersection1 = (t_intersection *) lst->content;
		// printf("%d" , intersection1->count);  
		intersection1->count = count;
		lst = lst->next;
	}
	// exit(0);
	return (xs);
}

t_color	color_at(t_world w, t_ray r)
{

	t_intersection	*i;
	t_intersection	h;
	t_comps			comps;

	i = intersect_world(w, r);
	h = hit(i);
	if (h.count == 0)
		return (color(0, 0, 0));
	comps = prepare_computations(h, r);
	return (shade_hit(w, comps));





	// t_list	*i;
	// t_intersection	h;
	// t_comps			comps;	
	// i = NULL;
	// i = intersect_world(w, r);
	// h = hit(i);
	// if (h.count == 0)
	// {
	// 	free(i);
	// 	return (color(0, 0, 0));
	// }
	// comps = prepare_computations(h, r);
	// free(i);
	// return (shade_hit(w, comps));
}