/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_parse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:16:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/12 17:57:27 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	comma_count(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			count++;
		i++;
	}
	return (count);
}

int	get_ambient_lighting(char **info_split, t_data *scene_data,
		char **color_split)
{
	int	ret;

	ret = 0;
	color_split = ft_split(info_split[2], ',');
	ret = parse_ambient_lighting(info_split, scene_data, color_split);
	free_2d_char_array(color_split);
	free(color_split);
	return (ret);
}

int	get_camera(char **info_split, t_data *scene_data, char **point_split,
		char **norm_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	norm_split = ft_split(info_split[2], ',');
	ret = parse_camera(info_split, scene_data, point_split, norm_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(norm_split);
	free(norm_split);
	return (ret);
}

int	get_light(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[3], ',');
	ret = parse_light(info_split, scene_data, point_split, color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	return (ret);
}

int	check_for_a_c_l(char **info_split, t_data *scene_data)
{
	char	**color_split;
	char	**norm_split;
	char	**point_split;

	color_split = NULL;
	norm_split = NULL;
	point_split = NULL;
	if (info_split[0][0] == 'A')
	{
		if (get_2darray_size(info_split) != 3)
			return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN AMBIENT LIGHT",
				scene_data));
		return (get_ambient_lighting(info_split, scene_data, color_split));
	}
	if (info_split[0][0] == 'C')
	{
		if (get_2darray_size(info_split) != 4)
			return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CAMERA",
				scene_data));
		return (get_camera(info_split, scene_data, point_split, norm_split));
	}
	if (info_split[0][0] == 'L')
	{
		if (get_2darray_size(info_split) != 4)
			return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN LIGHT",
				scene_data));
		return (get_light(info_split, scene_data, point_split, color_split));
	}
	return (set_error_obj(3, "INVALID IDENTIFIER", scene_data));
}
