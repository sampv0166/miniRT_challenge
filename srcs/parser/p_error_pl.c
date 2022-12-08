#include "../../includes/minirt.h"

int	error_checks_plane_split(t_data *scene_data, char **point_split,
	char **color_split, char **norm_split)
{
	if (get_2darray_size(point_split) != 3)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE POINT",
				scene_data));
	if (get_2darray_size(color_split) != 3)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE COLOR",
				scene_data));
	if (get_2darray_size(norm_split) != 3)
		return (set_error_obj(1,
				"WRONG NUMBER OF ARGUMENTS IN PLANE NORM VECTOR",
				scene_data));
	if (!verify_digits(point_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN PLANE POINT VALUES",
				scene_data));
	if (!verify_digits(color_split))
		return (set_error_obj(2, "ONLY DIGITS ALLOWED IN PLANE COLOR VALUES",
				scene_data));
	if (!verify_digits(norm_split))
		return (set_error_obj(2,
				"ONLY DIGITS ALLOWED IN PLANE NORM VECTOR VALUES",
				scene_data));
	return (1);
}

int	error_checks_plane(char **info, t_data *scene_data)
{
	if (get_2darray_size(info) != 4)
		return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE",
				scene_data));
	if (comma_count(info[1]) != 2)
		return (set_error_obj(1, "PLANE POINT FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[3]) != 2)
		return (set_error_obj(1, "PLANE COLOR FORMAT IS INCORRECT",
				scene_data));
	if (comma_count(info[2]) != 2)
		return (set_error_obj(1, "PLANE NORM VEC FORMAT IS INCORRECT",
				scene_data));
	return (1);
}
