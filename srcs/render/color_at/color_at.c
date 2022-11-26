#include "../../../includes/minirt.h"

t_ray	transform(t_ray r, double **m)
{
	t_ray		ret;
	t_tuple		tp1;
	t_tuple		tp2;
	t_tuple		multi1;
	t_tuple		multi2;
	t_point		p;
	t_vector	vec;

	// printf("inverse matrix\n");
	// print_matrix(m, 4);
	// printf("r\nay origin = \n");
	// print_point(r.origin);

	// printf("\nray diirection = \n");
	// print_vector(r.direction);


	tp1 = point_tp(r.origin);
	multi1 = matrix_multi_tp(m, tp1);
	tp2 = vector_tp(r.direction);
	multi2 = matrix_multi_tp(m, tp2);
	p = point(multi1.x, multi1.y, multi1.z);
	vec = vector(multi2.x, multi2.y, multi2.z);
	ret.origin = p;
	ret.direction = vec;

	// printf("ray origin\n");
	// print_point(ret.origin);

	// printf("ray diirection\n");
	// print_vector(ret.direction);
	// exit(0);
	return (ret);
}

t_intersect	intersect(t_shape *s, t_ray r)
{
	double **invrs;

	invrs = inverse(s->transform, 4);
	s->ray_in_obj_space = transform(r, invrs);

	free_2d_array(invrs, 4);

	if (!ft_strncmp(s->shape_name, "sp", 2))
	{
		// static int i;
		// 	printf("\n%d\n", i++);
		return (local_intersect_sphere(s->ray_in_obj_space));
	}
	else if(!ft_strncmp(s->shape_name, "pl", 2))
		return(local_intersect_plane(s->ray_in_obj_space));
	else if (!ft_strncmp(s->shape_name, "cy",2))
		return(local_intersect_cylinder(s->height , s->ray_in_obj_space));
	return (local_intersect_sphere(s->ray_in_obj_space));		
}


// void print_vector(t_vector *tp)
// {
//     printf("vec x = %f\n", tp->x);
//     printf("vec y = %f\n", tp->y);
//     printf("vec z = %f\n", tp->z);
// }

void print_tuple_sam( t_tuple *tp)
{
    printf("tp x = %f\n", tp->x);
    printf("tp y = %f\n", tp->y);
    printf("tp z = %f\n", tp->z);
    printf("tp w = %f\n", tp->w);
}

// t_intersect	intersect(t_shape *s, t_ray r)
// {
// 	t_intersect	inter;
// 	t_vector	sphere_to_ray;
// 	t_tuple		tp1;
// 	t_tuple		tp2;
// 	t_ray		r2;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		d;

// 	r2 = transform(r, inverse(s->transform, 4));
// 	sphere_to_ray = subtract_points(r2.origin, point(0, 0, 0));
// 	tp1 = vector_tp(r2.direction);
// 	a = dot(tp1, tp1);
// 	tp2 = vector_tp(sphere_to_ray);
// 	b = 2 * dot(tp1, tp2);
// 	c = dot(tp2, tp2) - 1;
// 	d = (b * b) - (4 * a * c);
// 	if (d < 0)
// 	{
// 		inter.count = 0;
// 		inter.t[0] = 0;
// 		inter.t[1] = 0;
// 		return (inter);
// 	}
// 	inter.count = 2;
// 	inter.t[0] = (-b - sqrt(d)) / (2 * a);
// 	inter.t[1] = (-b + sqrt(d)) / (2 * a);
// 	return (inter);
// }

// t_list	*intersect_world(t_world w, t_ray r)
// {
// 	t_list *xs;
// 	t_list *shapes;

// 	t_intersect inter;
// 	t_intersection *intersection1;
// 	t_intersection *intersection2;
// 	int i;
// 	int count;

// 	i = 0;
// 	count = 0;
// 	xs = NULL;
// 	t_shape *s;
// 	shapes = w.shapes;

// 	while (shapes)
// 	{
// 		s = (t_shape *) shapes->content;
// 		inter = intersect(*s, r);
// 		if (inter.count > 0)
// 		{
// 			intersection1 = malloc (sizeof (t_intersection));
// 			intersection2 = malloc (sizeof (t_intersection));

// 			intersection1->object = s;
// 			intersection1->t = inter.t[0];

// 			intersection2->object = s;
// 			intersection2->t = inter.t[1];
// 			if (i == 0)
// 			{
// 				xs = ft_lstnew(intersection1);
// 				ft_lstadd_back(&xs, ft_lstnew(intersection2));
// 			}
// 			else
// 			{
// 				ft_lstadd_back(&xs, ft_lstnew(intersection1));
// 				ft_lstadd_back(&xs, ft_lstnew(intersection2));
// 			}
// 			// intersection1 = (t_intersection *) xs->content;
// 			// printf("\n%f\n",intersection1->t);
// 			// intersection1 = (t_intersection *) xs->next->content;
// 			// printf("\n%f\n",intersection1->t);
// 			// 	printf("\n%f\n",intersection1->t);
// 			count = count + inter.count;
// 		}		shapes = shapes->next;		i++;
// 	}

// 	t_list *lst;
// 	lst = xs;

// 	while (lst)
// 	{

// 		intersection1 = (t_intersection *) lst->content;
// 		// printf("%d" , intersection1->count);  
// 		intersection1->count = count;
// 		lst = lst->next;
// 	}
// 	// exit(0);
// 	return (xs);
// }

t_list	*intersect_world(t_world w, t_ray r) 
{
	static int i;
	i++;
	t_list *intersections_list;
	t_list *shapes;
	t_intersect inter;
	t_shape *temp_shape;
	int first_check;
	t_intersection *intersection1;
	t_intersection *intersection2;
	
	first_check = 0;
	intersections_list = NULL;
	shapes = w.shapes;

	while (shapes)
	{	
		temp_shape = (t_shape *) shapes->content;
		inter = intersect(temp_shape, r);
		if (inter.count > 0)
		{
			// static int i;
			// printf("\n%d\n", i++);
			intersection1 = malloc (sizeof (t_intersection));
			intersection2 = malloc (sizeof (t_intersection));

			// printf("\nt1 = %f\n", inter.t[0]);
			// printf("\nt2 = %f\n", inter.t[1]);
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
	// printf("point\n");
	// print_point((r.origin));
	// exit(0);

	t_list	*intersections_list;
	t_comps			comps;
	t_intersection	*inter;

	intersections_list = intersect_world(w, r);
	inter  = hit(intersections_list );

	if (inter->count == 0)
		return (color(0, 0, 0));
	
	comps = prepare_computations(inter, r);
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