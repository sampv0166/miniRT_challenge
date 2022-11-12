#include "../../includes/minirt.h"

void	sort_intersections(t_list *xs)
{
	t_list *temp1;
	t_list *temp2;
	temp1 = xs;
	temp2 = xs;
	t_intersection *intersection1;
	t_intersection *intersection2;
	t_intersection *tempinter;
	while (temp1)
	{
		intersection1 = temp1->content;
		temp2 = xs;
		while(temp2)
		{
			intersection2 = temp2->content;
			if (intersection1->t > intersection2->t)
			{
				tempinter = intersection1;
				intersection1 = intersection2;
				intersection2 = tempinter; 
			}
			temp2 = temp2->next;
		}
		temp1= temp1->next ;
	}
	// int				i;
	// int				j;
	// t_intersection	*a;

	// i = 0;
	// a = xs->content;
	// // printf("count : %d\n", xs[0].count);
	// while (xs && i < a->count)
	// {
	// 	j = i + 1;
	// 	while (j < a->count)
	// 	{
	// 		if (xs[i].t > xs[j].t)
	// 		{
	// 			a = xs[i];
	// 			xs[i] = xs[j];
	// 			xs[j] = a;
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
}

t_intersection	hit(t_list *xs)
{
	int				i;
	t_intersection	*inter;
	t_intersection	inter2;
	t_list *temp;

	temp  = xs;

	i = 0;
	if (xs)
	{
		sort_intersections(xs);
		while (temp)
		{
			inter = temp->content;
			if (inter->t > 0.0)
				return(*inter);
			i++;
			temp = temp->next;
		}
	}	
	inter2.count = 0;
	inter2.t = 0;
	return (inter2);
}