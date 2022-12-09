/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   o_normal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:12:30 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/10 02:36:14 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	magnitude(t_vector vec)
{
	double		ret;
	double		sum;
	t_vector	tmp;

	tmp.x = pow(vec.x, 2);
	tmp.y = pow(vec.y, 2);
	tmp.z = pow(vec.z, 2);
	sum = tmp.x + tmp.y + tmp.z;
	ret = sqrt(sum);
	return (ret);
}

t_vector	normalize(t_vector vec)
{
	t_vector	ret;
	double		mag;

	mag = magnitude(vec);
	if (mag == 0)
	{
		ret.x = 0;
		ret.y = 0;
		ret.z = 0;
	}
	else
	{
		ret.x = vec.x / mag;
		ret.y = vec.y / mag;
		ret.z = vec.z / mag;
	}
	return (ret);
}
