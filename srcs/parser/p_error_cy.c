/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_error_cy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:13:32 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:13:32 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	error_check_split_cy(t_data *scene_data, char **point_split,
			char **color_split, char **norm_split)
{
	if (get_2darray_size(point_split) != 3)
		return (set_error_obj(1, "WRONG NO OF ARGUMENTS IN CYLINDER POINT",
				scene_data));
	if (get_2darray_size(color_split) != 3)
		return (set_error_obj(1, "WRONG NO OF ARGUMENTS IN CYLINDER COLOR",
				scene_data));
	if (get_2darray_size(norm_split) != 3)
		return (set_error_obj(1,
				"WRONG NO OF ARGUMENTS IN CYLINDER NORM VECTOR", scene_data));
	if (!verify_digits(point_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CYLINDER POINT VALUES",
				scene_data));
	if (!verify_digits(color_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CYLINDER COLOR VALUES",
				scene_data));
	if (!verify_digits(norm_split))
		return (set_error_obj(2,
				"ONLY DIGITS ALLOWED IN CYLINDER NORM VECTOR VALUES",
				scene_data));
	return (1);
}

int	error_check_base(char **info, t_data *scene_data)
{
	if (get_2darray_size(info) != 6)
		return (set_error_obj(1, "WRONG NO OF ARGUMENTS IN CYLINDER",
				scene_data));
	if (comma_count(info[1]) != 2)
		return (set_error_obj(1, "CYLINDER POINT FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[5]) != 2)
		return (set_error_obj(1, "CYLINDER COLOR FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[2]) != 2)
		return (set_error_obj(1, "CYLINDER NORM VEC FORMAT IS INCORRECT",
				scene_data));
	if (skip_dot_verify_digits(info[3]))
		return (set_error_obj(1, "DIAMETER OF CYLINDER SHOULD BE A NUMBER",
				scene_data));
	if (skip_dot_verify_digits(info[3]))
		return (set_error_obj(1, "HEIGHT OF CYLINDER SHOULD BE A NUMBER",
				scene_data));
	return (1);
}
