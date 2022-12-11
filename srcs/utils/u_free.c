/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:29:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/11 19:32:03 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	free_2d_array(double **arr, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_2d_char_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free_memmory(&arr[i]);
		i++;
	}
	free_memmory(arr);
}

void	free_scene_data(t_data *scene_data)
{
	t_list	*temp;
	t_shape	*sp;

	if (scene_data->num_objs.num_cam > 0)
	{
		free_2d_array(scene_data->camera2.transform, 4);
	}
	while (scene_data->wrld.shapes)
	{
		temp = scene_data->wrld.shapes->next;
		sp = (t_shape *) scene_data->wrld.shapes->content;
		free_2d_array(sp->transform, 4);
		if (sp->inverse)
			free_2d_array(sp->inverse, 4);
		free(sp);
		free(scene_data->wrld.shapes);
		scene_data->wrld.shapes = temp;
	}
}
