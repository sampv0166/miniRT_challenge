/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_cylinder.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:13:08 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:13:08 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	add_cylinder_transform(t_shape *cy)
{
	double		**translate;
	double		**rotate;
	double		**scale;
	double		**transform;
	double		radius;

	radius = cy->diameter * 0.5;
	scale = scaling(tuple (radius, cy->height * 0.5, radius, 1));
	translate = translation(tuple (cy->position.x,
				cy->position.y, cy->position.z, 1));
	transform = matrix_multi(translate, scale);
	free_2d_array(translate, 4);
	rotate = normal_rotation_matrix(tuple(cy->norm_vector.x,
				cy->norm_vector.y, cy->norm_vector.z, 0));
	translate = matrix_multi(rotate, transform);
	cy->transform = translate;
	cy->inverse = inverse(translate, 4);
	free_2d_array(rotate, 4);
	free_2d_array(transform, 4);
	free_2d_array(scale, 4);
}

void	populate_cylinder_split(t_shape *cy,
		char **point_split, char **norm_vec)
{
	cy->position.x = parse_double(point_split[0]);
	cy->position.y = parse_double(point_split[1]);
	cy->position.z = parse_double(point_split[2]);
	cy->norm_vector.x = parse_double(norm_vec[0]);
	cy->norm_vector.y = parse_double(norm_vec[1]);
	cy->norm_vector.z = parse_double(norm_vec[2]);
}

t_shape	*populate_cylinder_basic(t_data *scene_data, char **info,
		t_color *color)
{
	t_shape	*cy;

	cy = malloc (sizeof (t_shape));
	cy->color.r = color->r;
	cy->color.g = color->g;
	cy->color.b = color->b;
	cy->diameter = parse_double(info[3]);
	cy->height = parse_double(info[4]);
	cy->shape_name = "cy";
	cy->material.shininess = 200.0;
	cy->material.diffuse = 0.7;
	cy->material.specular = 0.2;
	cy->material.ambient = scene_data->amb_ratio;
	cy->material.color.r = cy->color.r / 255;
	cy->material.color.b = cy->color.b / 255;
	cy->material.color.g = cy->color.g / 255;
	return (cy);
}

int	parse_cylinder(char **info, t_data *scene_data, char **point_split,
	char **color_split)
{
	t_color	color;
	char	**norm_split;
	t_shape	*cy;

	norm_split = ft_split(info[2], ',');
	if (!error_check_base(info, scene_data))
		return (0);
	if (!error_check_split_cy(scene_data, point_split, color_split,
			norm_split))
		return (0);
	if (!parse_color(info[5], &color))
		return (set_error_obj(2, "CYLINDER COLOR VALUE IS WRONG", scene_data));
	cy = populate_cylinder_basic(scene_data, info, &color);
	populate_cylinder_split(cy, point_split, norm_split);
	add_cylinder_transform(cy);
	ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(cy));
	if (cy->inverse == NULL)
		return (set_error_obj(2, "CYLINDER MATRIX IS NOT INVERTIBLE",
				scene_data));
	scene_data->num_objs.num_cy += 1;
	free_2d_char_array(norm_split);
	free(norm_split);
	return (1);
}
