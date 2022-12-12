/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_ambient.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:13:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/12 21:26:40 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	check_str(char *str, int *dot_count, int i)
{
	while (i < str[i])
	{
		if (i == 0 && str[i] == '-')
		{
			i++;
			continue ;
		}
		if (str[i] == '.')
		{
			(*dot_count)++;
			i++;
			continue ;
		}
		if ((str[i] >= '0' && str[i] <= '9'))
		{
			i++;
			continue ;
		}
		else
			return (1);
		i++;
	}
	if (i == 1 && str[0] == '-')
		return (1);
	return (0);
}

int	skip_dot_verify_digits(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	if (check_str(str, &dot_count, i))
		return (1);
	if (ft_strlen(str) == 1 && *str == '.')
		return (1);
	if (dot_count > 1)
		return (1);
	return (0);
}

int	parse_ambient_lighting(char **info, t_data *scene_data, char **color_split)
{
	if (scene_data->num_objs.num_ambiance == 1)
		return (set_error_obj(1, "AMBIENCE IS ALREADY SET", scene_data));
	if (skip_dot_verify_digits(info[1]))
		return (set_error_obj(1, "AMBIENCE RATIO IS NOT A NUMBER", scene_data));
	scene_data->amb_ratio = parse_double(info[1]);
	if (scene_data->amb_ratio < 0 || scene_data->amb_ratio > 1)
		return (set_error_obj(1, "AMBIENCE RATIO SHOULD BE BETWEEN 1 AND 0",
				scene_data));
	if (comma_count(info[2]) != 2)
		return (set_error_obj(1, "AMBIENT LIGHTING COLOR FORMAT IS INCORRECT",
				scene_data));
	scene_data->num_objs.num_ambiance += 1;
	if (!verify_digits(color_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN AMBIENCE COLOR VALUES",
				scene_data));
	if (!parse_color(info[2], &scene_data->amb_color))
		return (set_error_obj(2, "AMBIENCE COLOR VALUE IS WRONG", scene_data));
	scene_data->amb_color.r = scene_data->amb_color.r / 255;
	scene_data->amb_color.g = scene_data->amb_color.g / 255;
	scene_data->amb_color.b = scene_data->amb_color.b / 255;
	return (1);
}
