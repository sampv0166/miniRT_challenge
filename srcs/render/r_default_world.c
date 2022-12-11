/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   r_default_world.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:28:00 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/11 19:16:19 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	default_world(t_data *scene_data)
{
	scene_data->wrld.l = point_light(scene_data->light_src.pos,
			scene_data->light_src.color, scene_data->light_src.ratio);
	if (scene_data->light_src.ratio == 0)
	{
		scene_data->wrld.l.color.r = 0.00001;
		scene_data->wrld.l.color.g = 0.00001;;
		scene_data->wrld.l.color.b = 0.00001;;
	}
	scene_data->wrld.l.color.r = scene_data->wrld.l.color.r  + scene_data->amb_color.r;
	scene_data->wrld.l.color.g = scene_data->wrld.l.color.g  + scene_data->amb_color.g;
	scene_data->wrld.l.color.b = scene_data->wrld.l.color.b  + scene_data->amb_color.b;
	// scene_data->wrld.l.pos = scene_data->light_src.pos;
	// scene_data->wrld.l.color.r = scene_data->wrld.l.color.r * scene_data->wrld.l.ratio;
	// scene_data->wrld.l.color.g = scene_data->wrld.l.color.g * scene_data->wrld.l.ratio;
	// scene_data->wrld.l.color.b = scene_data->wrld.l.color.b * scene_data->wrld.l.ratio;
	// 	sp->material.color.r = sp->material.color.r * scene_data->amb_ratio;
	// sp->material.color.g = sp->material.color.g * scene_data->amb_ratio;
	// sp->material.color.b = sp->material.color.b * scene_data->amb_ratio;
}