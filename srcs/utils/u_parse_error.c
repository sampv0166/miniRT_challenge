/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 13:26:05 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 16:09:19 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_for_a(char **info_split, t_data *scene_data, char	**color_split)
{
	if (get_2darray_size(info_split) != 3)
		return (set_error_obj(1,
				"WRONG NUMBER OF ARGUMENTS IN AMBIENT LIGHT",
				scene_data));
	return (get_ambient_lighting(info_split, scene_data, color_split));
}

int	check_for_c(char **info_split, t_data *scene_data, char	**norm_split,
		char	**point_split)
{
	if (get_2darray_size(info_split) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CAMERA",
				scene_data));
	return (get_camera(info_split, scene_data, point_split, norm_split));
}

int	check_for_l(char **info_split, t_data *scene_data, char	**color_split,
		char	**point_split)
{
	if (get_2darray_size(info_split) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN LIGHT",
				scene_data));
	return (get_light(info_split, scene_data, point_split, color_split));
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
		return (check_for_a(info_split, scene_data, color_split));
	else if (info_split[0][0] == 'C')
		return (check_for_c(info_split, scene_data, norm_split, point_split));
	else if (info_split[0][0] == 'L')
		return (check_for_l(info_split, scene_data, color_split, point_split));
	else
		return (set_error_obj(3, "INVALID IDENTIFIER", scene_data));
}
