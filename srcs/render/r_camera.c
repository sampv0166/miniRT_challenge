
#include "../../includes/minirt.h"

double	**view_transform(t_point from, t_point to, t_vector up)
{
	double		**m;
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_tuple		tp;

	forward = normalize(subtract_points(to, from));
	left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	m = identity_matrix();
	m[0][0] = left.x;
	m[0][1] = left.y;
	m[0][2] = left.z;
	m[1][0] = true_up.x;
	m[1][1] = true_up.y;
	m[1][2] = true_up.z;
	m[2][0] = forward.x * -1;
	m[2][1] = forward.y * -1;
	m[2][2] = forward.z * -1;
	tp = tuple((from.x * -1), (from.y * -1), (from.z * -1), 1);
	
	double **tr = translation(tp);
	double **r = matrix_multi(m, tr);
	
	free_2d_array(m, 4);
	free_2d_array(tr, 4);
	return (r);
}

// t_camera2	camera(double hsize, double vsize, double field_of_view)
// {
// 	t_camera2	c;
// 	double		half_view;
// 	double		aspect;

// 	c.hsize = hsize;
// 	c.vsize = vsize;
// 	c.field_of_view = field_of_view;
// 	//c.transform = identity_matrix();
// 	half_view = tan(c.field_of_view / 2);
// 	aspect = c.hsize / c.vsize;
// 	if (aspect >= 1)
// 	{
// 		c.half_width = half_view;
// 		c.half_height = half_view / aspect;
// 	}
// 	else
// 	{
// 		c.half_width = half_view * aspect;
// 		c.half_height = half_view;
// 	}
// 	c.pixel_size = (c.half_width * 2) / c.hsize;
// 	return (c);
// }

double	degrees_to_radians(double degr)
{
	return ((degr * M_PI) / 180.0);
}


t_camera2	camera(double hsize, double vsize, double field_of_view)
{
	t_camera2	c;
	double		half_view;
	double		aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	// c.transform = identity_matrix();
	half_view = tan( degrees_to_radians (field_of_view) / 2);
	aspect = c.hsize / c.vsize;
	if (aspect >= 1)
	{
		c.half_width = half_view;
		c.half_height = half_view / aspect;
	}
	else
	{
		c.half_width = half_view * aspect;
		c.half_height = half_view;
	}
	c.pixel_size = (c.half_width * 2) / c.hsize;
		// printf("\npixel size  = %f\n", c.pixel_size);
	// exit(0);
	return (c);
}
