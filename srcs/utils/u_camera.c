/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 12:51:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 15:36:47 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	camera_transform(t_data *scene_data)
{
	double		**transform;
	t_point		from;
	t_point		to;
	t_vector	up;
	t_tuple		origin_tp;

	from = point(scene_data->camera.pos.x, scene_data->camera.pos.y,
			scene_data->camera.pos.z);
	to = point(scene_data->camera.norm_vector.x,
			scene_data->camera.norm_vector.y,
			scene_data->camera.norm_vector.z);
	up = vector(0, 1, 0);
	transform = view_transform(from, to, vector(0, 1, 0));
	scene_data->camera2.transform = transform;
	scene_data->camera2 = camera(WIDTH, HEIGHT, scene_data->camera.fov);
	scene_data->camera2.transform = inverse(transform, 4);
	if (scene_data->camera2.transform)
	{
		origin_tp = matrix_multi_tp(scene_data->camera2.transform,
				tuple(0, 0, 0, 1));
		scene_data->camera2.origin = point(origin_tp.x,
				origin_tp.y, origin_tp.z);
	}
	free_2d_array(transform, 4);
}
