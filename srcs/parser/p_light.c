/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_light.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:13:04 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/10 02:43:40 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	light_error_check(char **info, t_data *scene_data)
{
	if (scene_data->num_objs.num_light == 1)
		return (set_error_obj(1, "LIGHT IS ALREADY SET", scene_data));
	if (get_2darray_size(info) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN LIGHT",
				scene_data));
	if (skip_dot_verify_digits(info[2]))
		return (set_error_obj(1, "LIGHT RATIO SHOULD BE A NUMBER", scene_data));
	scene_data->light_src.ratio = parse_double(info[2]);
	if (scene_data->light_src.ratio < 0 || scene_data->light_src.ratio > 1)
		return (set_error_obj(1, "LIGHT RATIO SHOULD BE BETWEEN 0 AND 1",
				scene_data));
	if (comma_count(info[1]) != 2)
		return (set_error_obj(1, "LIGHT POINT FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[3]) != 2)
		return (set_error_obj(1, "LIGHT COLOR FORMAT IS INCORRECT",
				scene_data));
	return (1);
}

void	normalize_light_color(t_data *scene_data)
{
	// scene_data->light_src.color.r = parse_double(color_split[0]);
	// scene_data->light_src.color.g = parse_double(color_split[1]);
	// scene_data->light_src.color.b = parse_double(color_split[2]);
	scene_data->light_src.color.r = scene_data->light_src.color.r / 255;
	scene_data->light_src.color.g = scene_data->light_src.color.g / 255;
	scene_data->light_src.color.b = scene_data->light_src.color.b / 255;
}

int	parse_light(char **info, t_data *scene_data, char **point_split,
		char **color_split)
{
	if (!light_error_check(info, scene_data))
		return (0);
	if (get_2darray_size(point_split) != 3)
		return (set_error_obj(2, "LIGHT POINT SHOULD HAVE 3 VALUES",
				scene_data));
	if (get_2darray_size(color_split) != 3)
		return (set_error_obj(2, "LIGHT COLOR SHOULD HAVE 3 VALUES",
				scene_data));
	if (!verify_digits(point_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN LIGHT POINT VALUES",
				scene_data));
	if (!verify_digits(color_split))
		return (set_error_obj(2,
				"ONLY DIGITS ALLOWED IN LIGHT COLOR VALUES",
				scene_data));
	if (!parse_color(info[3], &scene_data->light_src.color))
		return (set_error_obj(2, "LIGHT COLOR VALUE IS WRONG", scene_data));			
	scene_data->light_src.pos.x = parse_double(point_split[0]);
	scene_data->light_src.pos.y = parse_double(point_split[1]);
	scene_data->light_src.pos.z = parse_double(point_split[2]);
	normalize_light_color(scene_data);
	scene_data->num_objs.num_light += 1;
	return (1);
}
