#ifndef RENDER_H
# define RENDER_H

# include "common.h"

// Lighting
t_point		effective_color(t_material m, t_light l);
t_color		color_return(t_color ambient, t_color diffuse, t_color specular);
t_color		calc_ambient(t_comps c, t_light l);
t_color		calc_diffuse(t_comps c, t_light l, t_vector lightv);
t_color		calc_specular(t_material m, t_light l, double reflect_dot_eye);
t_vector	reflect(t_vector vec, t_vector normal);
t_light		point_light(t_point pos, t_color intensity);
t_material	material(void);
double		light_dot_normal(t_vector lightv, t_vector normalv);
double		reflect_dot_eye(t_vector reflectv, t_vector eyev);
t_color		lighting(t_comps c, t_light l, t_bool in_shadow);

#endif