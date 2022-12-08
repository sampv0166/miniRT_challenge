#include "../../includes/minirt.h"

int	check_str(char *str, int *dot_count, int i)
{
	while (i < str[i])
	{
		if (i == 0 && str[i] == '-')
		{
			i++;
			continue ;
		}
		if (str[i] == '.')
		{
			(*dot_count)++;
			i++;
			continue ;
		}
		if ((str[i] >= '0' && str[i] <= '9'))
		{
			i++;
			continue ;
		}
		else
			return (1);
		i++;
	}
	return (1);
}

int	skip_dot_verify_digits(char *str)
{
	int	i;
	int	dot_count;

	i = 0;
	dot_count = 0;
	check_str(str, &dot_count, i);
	if (ft_strlen(str) == 1 && *str == '.')
		return (1);
	if (dot_count > 1)
		return (1);
	return (0);
}

int	parse_ambient_lighting(char **info, t_data *scene_data, char **color_split)
{
	if (scene_data->num_objs.num_ambiance == 1)
		return (set_error_obj(1, "AMBIENCE IS ALREADY SET", scene_data));
	if (get_2darray_size(info) != 3)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN AMBIENT LIGHT",
				scene_data));
	if (skip_dot_verify_digits(info[1]))
		return (set_error_obj(1, "AMBIENCE RATIO IS NOT A NUMBER", scene_data));
	scene_data->amb_ratio = parse_double(info[1]);
	if (scene_data->amb_ratio < 0 || scene_data->amb_ratio > 1)
		return (set_error_obj(1, "AMBIENCE RATIO SHOULD BE BETWEEN 1 AND 0",
				scene_data));
	if (comma_count(info[2]) != 2)
		return (set_error_obj(1, "AMBIENT LIGHTING COLOR FORMAT IS INCORRECT",
				scene_data));
	scene_data->num_objs.num_ambiance += 1;
	if (!verify_digits(color_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN AMBIENCE COLOR VALUES",
				scene_data));
	if (!parse_color(info[2], &scene_data->amb_color))
		return (set_error_obj(2, "AMBIENCE COLOR VALUE IS WRONG", scene_data));
	return (1);
}
