/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_parse_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:29:16 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:29:16 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	error_check_color(char **rgb)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (skip_dot_verify_digits(rgb[i]))
		{
			free_2d_char_array(rgb);
			free(rgb);
			return (0);
		}
		i++;
	}
	return (1);
}

int	parse_color(char *str, t_color *colors)
{
	char	**rgb;
	double	c[3];

	rgb = ft_split(str, ',');
	if (get_2darray_size(rgb) != 3)
		return (0);
	if (!error_check_color(rgb))
		return (0);
	c[0] = parse_double(rgb[0]);
	c[1] = parse_double(rgb[1]);
	c[2] = parse_double(rgb[2]);
	if ((c[0] > 255 || c[0] < 0)
		|| (c[1] > 255 || c[1] < 0)
		|| (c[2] > 255 || c[2] < 0))
	{
		free_2d_char_array(rgb);
		free(rgb);
		return (0);
	}
	free_2d_char_array(rgb);
	free(rgb);
	colors->r = c[0];
	colors->g = c[1];
	colors->b = c[2];
	return (1);
}
