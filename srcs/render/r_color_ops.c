/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_color_ops.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:52 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:27:52 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_color	color(double red, double green, double blue)
{
	t_color	new;

	new.r = red;
	new.g = green;
	new.b = blue;
	return (new);
}
