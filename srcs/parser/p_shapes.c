#include "../../includes/minirt.h"

int	get_sphere(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[3], ',');
	ret = parse_sphere(info_split, scene_data, point_split, color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	return (ret);
}

int	get_plane(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[3], ',');
	ret = parse_plane(info_split, scene_data, point_split,
			color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	return (ret);
}

int	get_cylinder(char **info_split, t_data *scene_data, char **point_split,
		char **color_split)
{
	int	ret;

	point_split = ft_split(info_split[1], ',');
	color_split = ft_split(info_split[5], ',');
	ret = parse_cylinder(info_split, scene_data, point_split,
			color_split);
	free_2d_char_array(point_split);
	free(point_split);
	free_2d_char_array(color_split);
	free(color_split);
	return (ret);
}

int	check_for_sp_pl_cy(char **info_split, t_data *scene_data)
{
	char	**color_split;
	char	**point_split;

	color_split = NULL;
	point_split = NULL;
	if (info_split[0][0] == 's' && info_split[0][1] == 'p')
		return (get_sphere(info_split, scene_data, point_split, color_split));
	if (info_split[0][0] == 'p' && info_split[0][1] == 'l')
		return (get_plane(info_split, scene_data, point_split,
				color_split));
	if (info_split[0][0] == 'c' && info_split[0][1] == 'y')
		return (get_cylinder(info_split, scene_data, point_split, color_split));
	return (set_error_obj(3, "INVALID IDENTIFIER", scene_data));
}

int	parse_current_line(char *line, t_data *scene_data)
{
	char	**info_split;

	info_split = NULL;
	replace_tabs_and_newline(line);
	info_split = ft_split(line, ' ');
	scene_data->line_ptr = line;
	if (info_split && ft_strlen(info_split[0]) == 1)
	{
		if (!check_for_a_c_l(info_split, scene_data))
		{
			free_2d_char_array(info_split);
			return (0);
		}
	}
	else if (info_split && ft_strlen(info_split[0]) == 2)
	{
		if (!check_for_sp_pl_cy(info_split, scene_data))
		{
			free_2d_char_array(info_split);
			return (0);
		}
	}
	free_2d_char_array(info_split);
	free(info_split);
	return (1);
}
