/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error_cam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:13:11 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/12 17:56:03 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	camera_error_main(char **info, t_data *scene_data)
{
	if (scene_data->num_objs.num_cam == 1)
		return (set_error_obj(1, "CAMERA IS ALREADY SET", scene_data));
	if (skip_dot_verify_digits(info[3]))
		return (set_error_obj(1, "CAMERA FOV IS NOT A NUMBER", scene_data));
	scene_data->camera.fov = parse_double(info[3]);
	if (scene_data->camera.fov < 0 || scene_data->camera.fov > 180)
		return (set_error_obj(1, "CAMERA FOV SHOULD BE BETWEEN 0 AND 180",
				scene_data));
	if (comma_count(info[1]) != 2)
		return (set_error_obj(1, "CAMERA POINT FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[2]) != 2)
		return (set_error_obj(1, "CAMERA VECTOR FORMAT IS INCORRECT",
				scene_data));
	return (1);
}

int	camera_error_split(t_data *scene_data, char **point_split,
		char **norm_split)
{
	if (get_2darray_size(point_split) != 3)
		return (set_error_obj(2, "CAMERA POINT SHOULD HAVE 3 VALUES",
				scene_data));
	if (get_2darray_size(norm_split) != 3)
		return (set_error_obj(2, "CAMERA NORM VECTOR SHOULD HAVE 3 VALUES",
				scene_data));
	if (!verify_digits(point_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CAMERA POINT VALUES",
				scene_data));
	if (!verify_digits(norm_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CAMERA NORM VECTOR",
				scene_data));
	return (1);
}
