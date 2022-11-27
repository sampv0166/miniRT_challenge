#include "../../includes/minirt.h"

void	write_pixel(unsigned char *dst, double w, double h, t_color color, t_data *scene_data)
{
	int	rr;
	int	gg;
	int	bb;
	int	color_code ;

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
	double		xoffset;
	double		yoffset;
	double		world_x;
	double		world_y;
	t_point		p;
	t_tuple		multi1;
	t_point		pixel;
	t_vector	direction;

	xoffset = (x + 0.5) * camera.pixel_size;
	yoffset = (y + 0.5) * camera.pixel_size;
	world_x = camera.half_width - xoffset;
	world_y = camera.half_height - yoffset;
	p = point(world_x, world_y, -1);
	multi1 = matrix_multi_tp(camera.transform, point_tp(p));
	pixel = point(multi1.x, multi1.y, multi1.z);
	direction = normalize(subtract_points(pixel, camera.origin));
	return (ray(camera.origin, direction));
}

void	render(t_camera2 cam, t_world wrld, t_data *scene_data)
{
	double			w;
	double			h;
	t_ray			r;
	t_color			color;
	unsigned char	*dst;

	dst = NULL;
	h = 0;
	w = 0;
	while (h < HEIGHT)
	{
		w = 0;
		while (w < WIDTH)
		{
			r = ray_for_pixel(cam, w, h);
			color = color_at(wrld, r);
			write_pixel(dst, w, h, color, scene_data);
			w++;
		}
		h++;
	}
}