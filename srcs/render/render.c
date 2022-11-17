#include "../../includes/minirt.h"

void write_pixel(unsigned char *dst, double w, double h, t_color color,t_data *scene_data)
{
    int rr;
    int gg;
    int bb;
    int color_code ;
    
    rr = color.r * 255;
    gg = color.g * 255;
    bb = color.b * 255;

    color_code = rr << 16 | gg << 8 | bb;

    dst =  scene_data->img.data + (int)(h * scene_data->img.size_line +
    w * (scene_data->img.bits_per_pixel / 8));  

    	//     printf("\nr == %f\n", col.r);
    // printf("\ng == %f\n", col.g);
    //printf("\nb == %d\n", color_code);
    
    *(unsigned int*)dst  = color_code;
}

t_ray	ray_for_pixel(t_camera2 camera, double x, double y)
{
	double		xoffset;
	double		yoffset;
	double		world_x;
	double		world_y;
	t_point		p;
	t_tuple		multi1;
	t_tuple		multi2;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;
	double		**invrs;

	xoffset = (x + 0.5) * camera.pixel_size;
	yoffset = (y + 0.5) * camera.pixel_size;
	world_x = camera.half_width - xoffset;
	world_y = camera.half_height - yoffset;
	p = point(world_x, world_y, -1);
	invrs = inverse(camera.transform, 4);
	multi1 = matrix_multi_tp(invrs, point_tp(p));

	pixel = point(multi1.x, multi1.y, multi1.z);
	multi2 = matrix_multi_tp(invrs, tuple(0, 0, 0, 1));
	origin = point(multi2.x, multi2.y, multi2.z);
	// print_point("origin",&origin);
	direction = normalize(subtract_points(pixel, origin));
	free_2d_array(invrs, 4);
	return (ray(origin, direction));
}



void render(t_camera2 cam, t_world wrld, t_data *scene_data)
{
// t_shape *ss;
// ss = (t_shape *) scene_data->wrld.shapes->content;
// 	// 
// printf("%s" , ss->shape_name);
// 	exit(0);

    double w;
    double h;
    t_ray r;
    t_color color;
    unsigned char	*dst;
	dst = NULL;
    h = 0; 
    w = 0;
    while (h < HEIGHT - 1)
    {
        w = 0;
        while(w < WIDTH - 1)
        {
            r = ray_for_pixel(cam, w, h);
            color = color_at(wrld, r);       
			// exit(0);
            write_pixel(dst,w, h, color, scene_data);
            w++;
        }
		// printf("%f\n", w);
        h++;
    }
}