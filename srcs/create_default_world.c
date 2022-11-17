#include "../includes/minirt.h"

t_light	point_light(t_point pos, t_color intensity)
{
	t_light	l;

	l.pos = pos;
	l.color = intensity;
	return (l);
}


void default_world(t_data *scene_data)
{
	t_shape *sp;
			double	**translate;
		double	**scale;
		double	**transform;


    scene_data->wrld.l = point_light(scene_data->light_src.pos, 
                        (color(scene_data->light_src.ratio,
                        scene_data->light_src.ratio,scene_data->light_src.ratio)));
    
	// scene_data->wrld.shapes;
    // we can move the code for applying transformation here later if needed
	sp =  (t_shape*) scene_data->wrld.shapes->content;
	translate = translation(tuple( sp->position.x,sp->position.y, sp->position.z, 1));
	scale = scaling( tuple (sp->radius, sp->radius, sp->radius, 1));
	transform = matrix_multi(scale, translate);
	sp->transform = transform;
}  