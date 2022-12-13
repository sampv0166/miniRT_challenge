/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_sphere.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:33 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 14:14:25 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	verify_digits(char **str)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (skip_dot_verify_digits(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	add_sphere_transform(t_shape *sphere)
{
	double	**scale;
	double	**transform;
	double	**translate;

	translate = translation(tuple(sphere->position.x,
				sphere->position.y, sphere->position.z, 1));
	scale = scaling(tuple(sphere->radius / 2, sphere->radius / 2,
				sphere->radius / 2, 1));
	transform = matrix_multi(scale, translate);
	sphere->transform = transform;
	sphere->inverse = inverse(sphere->transform, 4);
	free_2d_array(translate, 4);
	free_2d_array(scale, 4);
}

t_shape	*populate_sphere(t_color color, char **point_split, char **info)
{
	t_shape	*sphere;

	sphere = malloc (sizeof (t_shape));
	sphere->color = color;
	sphere->position.x = parse_double(point_split[0]);
	sphere->position.y = parse_double(point_split[1]);
	sphere->position.z = parse_double(point_split[2]);
	sphere->radius = parse_double(info[2]);
	sphere->material.shininess = 200.0;
	sphere->material.diffuse = 0.7;
	sphere->material.specular = 0.2;
	sphere->material.color.r = sphere->color.r / 255;
	sphere->material.color.g = sphere->color.g / 255;
	sphere->material.color.b = sphere->color.b / 255;
	sphere->shape_name = "sp";
	sphere->material.ambient = 0.1;
	add_sphere_transform(sphere);
	return (sphere);
}

int	parse_sphere(char **info, t_data *scene_data, char **point_split,
		char **color_split)
{
	t_color	color;
	t_shape	*sphere;

	if (!error_checks(info, scene_data, point_split, color_split))
		return (0);
	if (!parse_color(info[3], &color))
		return (set_error_obj(2, "SPHERE COLOR VALUE IS WRONG",
				scene_data));
	sphere = populate_sphere(color, point_split, info);
	ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(sphere));
	if (sphere->inverse == NULL)
		return (set_error_obj(1, "SPHERE INVERSE MATRIX IS NOT INVERTIBLE",
				scene_data));
	scene_data->num_objs.num_sp += 1;
	return (1);
}
