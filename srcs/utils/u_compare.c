/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_compare.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:28:52 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	double_equal(double a, double b)
{
	if (fabs(a - b) < EPSILON)
		return (1);
	return (0);
}
