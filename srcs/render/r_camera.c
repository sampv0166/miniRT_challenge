/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_camera.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:43 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 15:32:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	**set_matrix(t_vector left, t_vector true_up, t_vector forward)
{
	double	**m;

	m = identity_matrix();
	m[0][0] = left.x;
	m[0][1] = left.y;
	m[0][2] = left.z;
	m[1][0] = true_up.x;
	m[1][1] = true_up.y;
	m[1][2] = true_up.z;
	m[2][0] = forward.x * -1;
	m[2][1] = forward.y * -1;
	m[2][2] = forward.z * -1;
	return (m);
}

void	init_vector(t_vector *vec)
{
	vec->x = 0;
	vec->y = 0;
	vec->z = 0;
}

double	**view_transform(t_point from, t_point to, t_vector up)
{
	double		**m;
	t_vector	v[3];
	t_tuple		tp;
	double		**translate;
	double		**ret;

	v[0] = vector(to.x, to.y, to.z);
	v[1] = cross(v[0], normalize(up));
	v[2] = cross(v[1], v[0]);
	m = set_matrix(v[1], v[2], v[0]);
	tp = tuple((from.x * -1), (from.y * -1), (from.z * -1), 1);
	translate = translation(tp);
	ret = matrix_multi(m, translate);
	free_2d_array(m, 4);
	free_2d_array(translate, 4);
	return (ret);
}

double	rad(double deg)
{
	return ((deg * M_PI) / 180.0);
}

t_camera2	camera(double hsize, double vsize, double field_of_view)
{
	t_camera2	c;
	double		half_view;
	double		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	half_view = tan(rad(field_of_view) / 2);
	aspect = c.hsize / c.vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}
