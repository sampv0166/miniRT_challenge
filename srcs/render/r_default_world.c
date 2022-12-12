/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_default_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/12 13:36:23 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	default_world(t_data *scene_data)
{
	scene_data->wrld.l = point_light(scene_data->light_src.pos,
			scene_data->light_src.color, scene_data->light_src.ratio);
	scene_data->wrld.l.ratio =  scene_data->light_src.ratio;
	scene_data->wrld.l.ambient_ratio =  scene_data->amb_ratio;
	// scene_data->wrld.l.pos = scene_data->light_src.pos;
	// scene_data->wrld.l.color.r = scene_data->wrld.l.color.r * scene_data->wrld.l.ratio;		
	// scene_data->wrld.l.color.g = scene_data->wrld.l.color.g * scene_data->wrld.l.ratio;
	// scene_data->wrld.l.color.b = scene_data->wrld.l.color.b * scene_data->wrld.l.ratio;
}