#include "../../includes/minirt.h"

void	write_pixel(double w, double h, t_color color, t_data *scene_data)
{
	int				rr;
	int				gg;
	int				bb;
	int				color_code;
	unsigned char	*dst;

	rr = color.r * 255;
	gg = color.g * 255;
	bb = color.b * 255;
	color_code = rr << 16 | gg << 8 | bb;
	dst = scene_data->img.data + (int)(h * scene_data->img.size_line
			+ w * (scene_data->img.bits_per_pixel / 8));
	*(unsigned int *)dst = color_code;
}

t_ray	ray_for_pixel(t_camera2 camera, double x, double y)
{
	double		offset[2];
	double		world[2];
	t_point		p[2];
	t_tuple		multi1;
	t_vector	direction;

	offset[0] = (x + 0.5) * camera.pixel_size;
	offset[1] = (y + 0.5) * camera.pixel_size;
	world[0] = camera.half_width - offset[0];
	world[1] = camera.half_height - offset[1];
	p[0] = point(world[0], world[1], -1);
	multi1 = matrix_multi_tp(camera.transform, point_tp(p[0]));
	p[1] = point(multi1.x, multi1.y, multi1.z);
	direction = normalize(subtract_points(p[1], camera.origin));
	return (ray(camera.origin, direction));
}

void	render(t_camera2 cam, t_world wrld, t_data *scene_data)
{
	double			w;
	double			h;
	t_ray			r;
	t_color			color;

	h = 0;
	w = 0;
	while (h < HEIGHT)
	{
		w = 0;
		while (w < WIDTH)
		{
			r = ray_for_pixel(cam, w, h);
			color = color_at(wrld, r);
			write_pixel(w, h, color, scene_data);
			w++;
		}
		h++;
	}
}
