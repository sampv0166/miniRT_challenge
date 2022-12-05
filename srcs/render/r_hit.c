#include "../../includes/minirt.h"

void	sort_intersections(t_list *xs)
{
	t_intersection	*inter1;
	t_intersection	*inter2;
	t_list			*temp;
	t_intersection	*temp_intersection;

	temp = xs;
	while (xs)
	{
		inter1 = (t_intersection *) xs->content;
		temp = xs->next;
		while (temp)
		{
			inter2 = (t_intersection *) temp->content;
			if (inter1->t > inter2->t)
			{
				temp_intersection = inter1;
				inter1 = inter2;
				inter2 = temp_intersection;
			}
			temp = temp->next;
		}
		xs = xs->next;
	}
}

void	find_min(t_list *xs, t_intersection **min_inter,
	double *min)
{
	t_intersection	*temp;

	while (xs)
	{
		temp = (t_intersection *) xs->content;
		// printf("\n hit = %f\n", temp->t);
		if (*min > temp->t && temp->t > EPSILON)
		{
			*min_inter = temp;
			*min = temp->t;
		}
		xs = xs->next;
	}
}

t_intersection	*hit(t_list *intersection_list)
{
	t_list			*xs;
	t_intersection	*inter;
	t_intersection	*min_inter;
	double			min;

	min_inter = NULL;
	min = __INT_MAX__;
	xs = intersection_list;
	inter = malloc(sizeof(t_intersection));
	if (xs)
	{
		// sort_intersections(xs);
		find_min(xs, &min_inter, &min);
		if (min_inter && min_inter->t > EPSILON)
		{
			// printf("\n smallest  = %f\n", min_inter->t);
			free(inter);
			return (min_inter);
		}
	}
	inter->count = 0;
	inter->t = 0;
	return (inter);
}
