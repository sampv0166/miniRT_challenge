/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_shapes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:29 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 16:01:18 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	get_sphere(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[3], ',');
	ret = parse_sphere(info_split, scene_data, point_split, color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	return (ret);
}

int	get_plane(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[3], ',');
	ret = parse_plane(info_split, scene_data, point_split,
			color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	free_2d_char_array(scene_data->norm_split_to_free);
	free(scene_data->norm_split_to_free);
	if (ret == 0)
		free(scene_data->shape_to_free);
	return (ret);
}

int	get_cylinder(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[5], ',');
	ret = parse_cylinder(info_split, scene_data, point_split,
			color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	free_2d_char_array(scene_data->norm_split_to_free);
	free(scene_data->norm_split_to_free);
	return (ret);
}

int	free_info(char	**info_split)
{
	free_2d_char_array(info_split);
	free(info_split);
	return (0);
}

int	parse_current_line(char *line, t_data *scene_data)
{
	char	**info_split;

	info_split = NULL;
	replace_tabs_and_newline(line);
	info_split = ft_split(line, ' ');
	scene_data->line_ptr = line;
	if (info_split && ft_strlen(info_split[0]) == 1)
	{
		if (!check_for_a_c_l(info_split, scene_data))
			return (free_info(info_split));
	}
	else if (info_split && ft_strlen(info_split[0]) == 2)
	{
		if (!check_for_sp_pl_cy(info_split, scene_data))
			return (free_info(info_split));
	}
	else
	{
		set_error_obj(3, "INVALID IDENTIFIER", scene_data);
		return (free_info(info_split));
	}
	free_2d_char_array(info_split);
	free(info_split);
	return (1);
}
