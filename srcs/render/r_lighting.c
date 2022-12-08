/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_lighting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:21 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:28:21 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	lighting(t_comps c, t_light l, t_bool in_shadow)
{
	t_vector	lightv;
	t_vector	reflectv;
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;

	lightv = normalize(subtract_points(point(l.pos.x, l.pos.y, l.pos.z),
				c.over_point));
	ambient = calc_ambient(c, l);
	if (light_dot_normal(lightv, c.normalv) < 0 || in_shadow)
	{
		diffuse = color(0, 0, 0);
		specular = color(0, 0, 0);
	}
	else
	{
		diffuse = calc_diffuse(c, l, lightv);
		reflectv = reflect(negate_vector(lightv), c.normalv);
		if (reflect_dot_eye(reflectv, c.eyev) <= 0)
			specular = color(0, 0, 0);
		else
			specular = calc_specular(c.object->material, l,
					reflect_dot_eye(reflectv, c.eyev));
	}
	return (color_return(ambient, diffuse, specular));
}
