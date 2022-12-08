#include "../../includes/minirt.h"

int	error_checks_basic(char **info, t_data *scene_data)
{
	if (get_2darray_size(info) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE",
				scene_data));
	if (skip_dot_verify_digits(info[2]))
		return (set_error_obj(1, "DIAMETER OF SPHERE SHOULD BE A NUMBER",
				scene_data));
	return (1);
}

int	error_checks_comma(char **info, t_data *scene_data)
{
	if (comma_count(info[1]) != 2)
		return (set_error_obj(1, "SPHERE POINT FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[3]) != 2)
		return (set_error_obj(1, "SPHERE COLOR FORMAT IS INCORRECT",
				scene_data));
	return (1);
}

int	error_checks_split(char **point_split, char **color_split,
		t_data *scene_data)
{
	if (get_2darray_size(point_split) != 3)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE POINT",
				scene_data));
	if (get_2darray_size(color_split) != 3)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN SPHERE COLOR",
				scene_data));
	if (!verify_digits(point_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN SPHERE POINT VALUES",
				scene_data));
	if (!verify_digits(color_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN SPHERE COLOR VALUES",
				scene_data));
	return (1);
}

int	error_checks(char **info, t_data *scene_data, char **point_split,
		char **color_split)
{
	if (!error_checks_basic(info, scene_data))
		return (0);
	if (!error_checks_comma(info, scene_data))
		return (0);
	if (!error_checks_split(point_split, color_split, scene_data))
		return (0);
	return (1);
}
