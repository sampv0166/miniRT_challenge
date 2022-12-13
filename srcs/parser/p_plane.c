/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_plane.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:16:07 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 15:23:04 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	**normal_rotation_matrix(t_tuple normal)
{
	double		angle;
	double		vals[3];
	t_vector	axis;
	double		**rotation;

	rotation = identity_matrix();
	angle = acos(dot(normal, tuple(0, 1, 0, 0)));
	axis = cross(vector(normal.x, normal.y, normal.z), vector(0, 1, 0));
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	rotation[0][0] = vals[0] + (pow(axis.x, 2) * vals[2]);
	rotation[0][1] = (axis.x * axis.y * vals[2]) - (axis.z * vals[1]);
	rotation[0][2] = (axis.x * axis.z * vals[2]) + (axis.y * vals[1]);
	rotation[1][0] = (axis.y * axis.z * vals[2]) + (axis.z * vals[1]);
	rotation[1][1] = vals[0] + (pow(axis.y, 2) * vals[2]);
	rotation[1][2] = (axis.y * axis.z * vals[2]) - (axis.x * vals[1]);
	rotation[2][0] = (axis.z * axis.x * vals[2]) - (axis.y * vals[1]);
	rotation[2][1] = (axis.z * axis.y * vals[2]) + (axis.x * vals[1]);
	rotation[2][2] = vals[0] + (pow(axis.z, 2) * vals[2]);
	rotation[3][3] = 1;
	return (rotation);
}

void	populate_plane(t_shape *plane, t_color *color,
	char **point_split, char **norm_vec)
{
	plane->color.r = color->r;
	plane->color.g = color->g;
	plane->color.b = color->b;
	plane->material.shininess = 200.0;
	plane->material.diffuse = 0.7;
	plane->material.specular = 0.2;
	plane->shape_name = "pl";
	plane->material.ambient = 0.1;
	plane->material.color.r = plane->color.r / 255;
	plane->material.color.g = plane->color.g / 255;
	plane->material.color.b = plane->color.b / 255;
	plane->position.x = parse_double(point_split[0]);
	plane->position.y = parse_double(point_split[1]);
	plane->position.z = parse_double(point_split[2]);
	plane->norm_vector.x = parse_double(norm_vec[0]);
	plane->norm_vector.y = parse_double(norm_vec[1]);
	plane->norm_vector.z = parse_double(norm_vec[2]);
}

int	add_plane(t_shape *plane, t_data *scene_data)
{
	double		**translate;
	double		**rotate;
	double		**transform;

	translate = translation(tuple (plane->position.x,
				plane->position.y, plane->position.z, 1));
	rotate = normal_rotation_matrix(tuple(plane->norm_vector.x,
				plane->norm_vector.y, plane->norm_vector.z, 0));
	transform = matrix_multi(translate, rotate);
	plane->transform = transform ;
	plane->inverse = inverse(plane->transform, 4);
	scene_data->tranform_to_free = plane->transform;
	scene_data->inverse_to_free = plane->inverse;
	free_2d_array(translate, 4);
	free_2d_array(rotate, 4);
	ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(plane));
	scene_data->num_objs.num_pl += 1;
	if (plane->inverse == NULL)
		return (set_error_obj(2, "PLANE MATRIX IS NOT INVERTIBLE", scene_data));
	return (1);
}

int	parse_plane(char **info, t_data *scene_data, char **point_split,
			char **color_split)
{
	t_color	color;
	char	**norm_split;
	t_shape	*plane;

	norm_split = ft_split(info[2], ',');
	scene_data->norm_split_to_free = norm_split;
	plane = malloc (sizeof (t_shape));
	scene_data->shape_to_free = plane;
	if (!error_checks_plane(info, scene_data))
		return (0);
	if (!error_checks_plane_split(scene_data, point_split,
			color_split, norm_split))
		return (0);
	if (!parse_color(info[3], &color))
		return (set_error_obj(2, "PLANE COLOR VALUE IS WRONG",
				scene_data));
	populate_plane(plane, &color, point_split, norm_split);
	if (norm_vector(&plane->norm_vector))
		return (set_error_obj(2,
				"PLANE ORIENTATION VECTOR SHOULD BE BETWEEN -1 and 1",
				scene_data));
	return (add_plane(plane, scene_data));
}
