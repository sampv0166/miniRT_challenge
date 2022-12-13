/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:13:04 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 13:32:45 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	store_in_scene_data(t_data *scene_data, char **point_split,
	char **norm_vec_split, char **info)
{
	scene_data->camera.pos.x = parse_double(point_split[0]);
	scene_data->camera.pos.y = parse_double(point_split[1]);
	scene_data->camera.pos.z = parse_double(point_split[2]);
	scene_data->camera.norm_vector.x = parse_double(norm_vec_split[0]);
	scene_data->camera.norm_vector.y = parse_double(norm_vec_split[1]);
	scene_data->camera.norm_vector.z = parse_double(norm_vec_split[2]);
	scene_data->camera.fov = parse_double(info[3]);
	if (scene_data->camera.norm_vector.x == 0
		&& scene_data->camera.norm_vector.y == 0
		&& scene_data->camera.norm_vector.z == 0)
		scene_data->camera.norm_vector.z = 1;
}

int	norm_vector(t_vector *vec)
{
	if (vec->x < -1 || vec->x > 1)
		return (1);
	if (vec->y < -1 || vec->y > 1)
		return (1);
	if (vec->z < -1 || vec->z > 1)
		return (1);
	return (0);
}

int	parse_camera(char **info, t_data *scene_data, char **point_split,
		char **norm_split)
{
	if (!camera_error_main(info, scene_data))
		return (0);
	if (!camera_error_split(scene_data, point_split, norm_split))
		return (0);
	store_in_scene_data(scene_data, point_split, norm_split, info);
	if (norm_vector(&scene_data->camera.norm_vector))
		return (set_error_obj(2,
				"CAMERA ORIENTATION VECTOR SHOULD BE BETWEEN -1 and 1",
				scene_data));
	camera_transform(scene_data);
	if (scene_data->camera2.transform == NULL)
		return (set_error_obj(2, "CAMERA MATRIX NOT INVERTIBLE", scene_data));
	scene_data->num_objs.num_cam += 1;
	return (1);
}
