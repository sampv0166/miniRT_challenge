#include "../../includes/minirt.h"

t_point	calculate_to(t_data *scene_data)
{
	t_tuple		to_tp_point;
	t_tuple		to_tp_vector;
	t_tuple		to_result;
	t_point		to;

	to_tp_point = tuple(scene_data->camera.norm_vector.x,
			scene_data->camera.norm_vector.y,
			scene_data->camera.norm_vector.z, 1);
	to_tp_vector = tuple(scene_data->camera.pos.x, scene_data->camera.pos.y,
			scene_data->camera.pos.z, 0);
	to_result = add(to_tp_point, to_tp_vector);
	to = point(to_result.x, to_result.y, to_result.z);
	return (to);
}

t_vector	calculate_up(t_data *scene_data)
{
	t_vector	up;
	t_vector	up1_vec;

	up1_vec = cross(scene_data->camera.norm_vector, vector(0, 1, 1));
	up = cross(up1_vec, scene_data->camera.norm_vector);
	return (up);
}

void	camera_transform(t_data *scene_data)
{
	double		**transform;
	t_point		from;
	t_point		to;
	t_vector	up;
	t_tuple		origin_tp;

	from = point(scene_data->camera.pos.x, scene_data->camera.pos.y,
			scene_data->camera.pos.z);
	to = calculate_to(scene_data);
	up = calculate_up(scene_data);
	transform = view_transform(from, to, up);
	scene_data->camera2.transform = transform;
	scene_data->camera2 = camera(WIDTH, HEIGHT, scene_data->camera.fov);
	scene_data->camera2.transform = inverse(transform, 4);
	origin_tp = matrix_multi_tp(scene_data->camera2.transform,
			tuple(0, 0, 0, 1));
	scene_data->camera2.origin = point(origin_tp.x, origin_tp.y, origin_tp.z);
	free_2d_array(transform, 4);
}

void	store_in_scene_data(t_data *scene_data, char **point_split,
	char **norm_vec_split, char **info)
{
	scene_data->camera.pos.x = parse_double(point_split[0]);
	scene_data->camera.pos.y = parse_double(point_split[1]);
	scene_data->camera.pos.z = parse_double(point_split[2]);
	scene_data->camera.norm_vector.x = parse_double(norm_vec_split[0]);
	scene_data->camera.norm_vector.y = parse_double(norm_vec_split[1]);
	scene_data->camera.norm_vector.z = parse_double(norm_vec_split[2]);
	scene_data->camera.fov = parse_double(info[3]);
}

int	parse_camera(char **info, t_data *scene_data, char **point_split,
		char **norm_split)
{
	if (!camera_error_main(info, scene_data))
		return (0);
	if (!camera_error_split(scene_data, point_split, norm_split))
		return (0);
	store_in_scene_data(scene_data, point_split, norm_split, info);
	camera_transform(scene_data);
	if (scene_data->camera2.transform == NULL)
		return (set_error_obj(2, "CAMERA MATIX NOT INVERTIBLE", scene_data));
	scene_data->num_objs.num_cam += 1;
	return (1);
}
