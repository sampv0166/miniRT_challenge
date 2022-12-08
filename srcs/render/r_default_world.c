/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_default_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:28:00 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	default_world(t_data *scene_data)
{
	scene_data->wrld.l = point_light(scene_data->light_src.pos,
			(color(scene_data->light_src.ratio, scene_data->light_src.ratio,
					scene_data->light_src.ratio)));
}
