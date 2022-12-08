/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_product.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:12:39 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:12:39 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	dot(t_tuple a, t_tuple b)
{
	double	ret;

	ret = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
	return (ret);
}

t_vector	cross(t_vector vec1, t_vector vec2)
{
	t_vector	ret;

	ret.x = vec1.y * vec2.z - vec1.z * vec2.y;
	ret.y = vec1.z * vec2.x - vec1.x * vec2.z;
	ret.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (ret);
}
