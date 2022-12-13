/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse_error2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:47:18 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 15:58:46 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_for_sp(char **info_split, t_data *scene_data, char **color_split,
	char	**point_split)
{
	if (get_2darray_size(info_split) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE",
				scene_data));
	return (get_sphere(info_split, scene_data, point_split, color_split));
}

int	check_for_pl(char **info_split, t_data *scene_data, char **color_split,
	char	**point_split)
{
	if (get_2darray_size(info_split) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE",
				scene_data));
	return (get_plane(info_split, scene_data, point_split,
			color_split));
}

int	check_for_cy(char **info_split, t_data *scene_data, char **color_split,
	char	**point_split)
{
	if (get_2darray_size(info_split) != 6)
		return (set_error_obj(1, "WRONG NO OF ARGUMENTS IN CYLINDER",
				scene_data));
	return (get_cylinder(info_split, scene_data, point_split, color_split));
}

int	check_for_sp_pl_cy(char **info_split, t_data *scene_data)
{
	char	**color_split;
	char	**point_split;

	color_split = NULL;
	point_split = NULL;
	if (info_split[0][0] == 's' && info_split[0][1] == 'p')
		return (check_for_sp(info_split, scene_data, color_split, point_split));
	else if (info_split[0][0] == 'p' && info_split[0][1] == 'l')
		return (check_for_pl(info_split, scene_data, color_split, point_split));
	else if (info_split[0][0] == 'c' && info_split[0][1] == 'y')
		return (check_for_cy(info_split, scene_data, color_split, point_split));
	else
		return (set_error_obj(3, "INVALID IDENTIFIER", scene_data));
}
