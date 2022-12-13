/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imustafa <imustafa@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:27:24 by imustafa          #+#    #+#             */
/*   Updated: 2022/12/13 16:42:55 by imustafa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	init_scene(t_data *scene_data)
{
	scene_data->num_objs.num_ambiance = 0;
	scene_data->num_objs.num_cam = 0;
	scene_data->num_objs.num_cy = 0;
	scene_data->num_objs.num_light = 0;
	scene_data->num_objs.num_pl = 0;
	scene_data->num_objs.num_sp = 0;
}

int	parse_line(int fd, t_data *scene_data)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line && *line != '#' && *line != '\n')
		{
			if (!parse_current_line(line, scene_data))
			{
				free_memmory(&line);
				return (0);
			}
		}
		else if (!line)
		{
			free_memmory(&line);
			break ;
		}
		free_memmory(&line);
	}
	return (1);
}

t_color	set_color(t_data *scene_data)
{
	t_color	color;

	color.r = scene_data->amb_color.r * scene_data->amb_ratio;
	color.g = scene_data->amb_color.g * scene_data->amb_ratio;
	color.b = scene_data->amb_color.b * scene_data->amb_ratio;
	return (color);
}

void	set_shapes(t_data *scene_data, t_color color)
{
	t_shape	*sp;
	t_list	*shapes;

	shapes = scene_data->wrld.shapes;
	while (shapes)
	{
		sp = (t_shape *) shapes->content;
		sp->material.ambient = scene_data->amb_ratio;
		sp->material.color.r = sp->material.color.r + color.r;
		sp->material.color.g = sp->material.color.g + color.g;
		sp->material.color.b = sp->material.color.b + color.b;
		shapes = shapes->next;
	}
}

int	parse_scene(char *file_name, t_data *scene_data)
{
	int		fd;

	init_scene(scene_data);
	if (!check_file_name(file_name))
		return (set_error_obj(1, "FILE EXTENTION IS INCORRECT", scene_data));
	fd = open(file_name, O_RDONLY);
	if (fd < 0 || read(fd, file_name, 0) < 0)
		return (set_error_obj(2, "FILE ERROR", scene_data));
	if (!parse_line(fd, scene_data))
		return (0);
	if (scene_data->num_objs.num_cam == 0)
		return (set_error_obj(1, "CAMERA IS NOT SET", scene_data));
	if (scene_data->num_objs.num_light == 0)
		return (set_error_obj(1, "LIGHT IS NOT SET", scene_data));
	if (scene_data->num_objs.num_ambiance == 0)
		return (set_error_obj(1, "AMBIENCE IS NOT SET", scene_data));
	set_shapes(scene_data, set_color(scene_data));
	close(fd);
	return (1);
}
