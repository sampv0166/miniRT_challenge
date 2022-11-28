#include "../../includes/minirt.h"

void	default_world(t_data *scene_data)
{
	scene_data->wrld.l = point_light(scene_data->light_src.pos,
			(color(scene_data->light_src.ratio, scene_data->light_src.ratio,
					scene_data->light_src.ratio)));
}
