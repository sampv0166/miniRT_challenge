/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apila-va <apila-va@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:12:04 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/10 02:35:49 by apila-va         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// Cylinder
int			check_cap(t_ray ray, double t);
t_intersect	intersect_caps(t_shape *cy, t_ray ray, t_intersect *i, t_list \
			**intersections_list);
void		init_intersect(t_intersect *inter1);
void		check_intersect(t_intersect *inter1, t_ray ray, \
			t_list **intersections_lst, t_shape *s);
void		set_intersect(t_intersect *inter1, t_ray ray, \
			t_list **intersections_lst, t_shape *s);

#endif