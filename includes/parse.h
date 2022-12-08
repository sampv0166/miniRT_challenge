/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:11:38 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/08 18:11:38 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "common.h"

int		check_file_name(char *file_name);
void	replace_tabs_and_newline(char *line);
double	parse_double(char *str);
int		get_2darray_size(char **arr);
int		parse_color(char *str, t_color *colors);
void	free_2d_char_array(char **arr);
int		skip_dot_verify_digits(char *str);
int		parse_scene(char *file_name, t_data *scene_data);
int		parse_camera(char **info, t_data *scene_data, char **point_split,
			char **norm_split);
int		parse_sphere(char **info, t_data *scene_data, char **point_split,
			char **color_split);
int		parse_plane(char **info, t_data *scene_data, char **point_split,
			char **color_split);
int		parse_cylinder(char **info, t_data *scene_data, char **point_split,
			char **color_split);
int		parse_ambient_lighting(char **info, t_data *scene_data,
			char **color_split);
int		parse_light(char **info, t_data *scene_data, char **point_split,
			char **color_split );
int		check_for_a_c_l(char **info_split, t_data *scene_data);
int		parse_current_line(char *line, t_data *scene_data);
int		error_checks_basic(char **info, t_data *scene_data);
int		error_checks_comma(char **info, t_data *scene_data);
int		error_checks_split(char **point_split, char **color_split,
			t_data *scene_data);
int		error_checks(char **info, t_data *scene_data, char **point_split,
			char **color_split);
int		error_check_split_cy(t_data *scene_data, char **point_split,
			char **color_split, char **norm_split);
int		error_check_base(char **info, t_data *scene_data);
void	add_cylinder_transform(t_shape *cy);
int		error_checks_plane_split(t_data *scene_data, char **point_split,
			char **color_split, char **norm_split);
int		error_checks_plane(char **info, t_data *scene_data);
int		camera_error_main(char **info, t_data *scene_data);
int		camera_error_split(t_data *scene_data, char **point_split,
			char **norm_split);

#endif