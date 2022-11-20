#include "./includes/minirt.h"

/*
The first thing is to check the arguments
Then its parsing the data
setup mlx and exit the window
create world from the parsed data
setup the camera
render the scene
display the window
*/

int	key(int keycode, t_data *scene_data)
{
	if (keycode)
	{
		mlx_destroy_window(scene_data->mlx.mlx_ptr, scene_data->mlx.win_ptr);
		free_scene_data(scene_data);
		exit (0);
	}
	return (0);
}

void	setup_mlx(t_data *scene_data)
{
	scene_data->mlx.mlx_ptr = malloc(sizeof(*scene_data->mlx.mlx_ptr));
	scene_data->mlx.mlx_ptr = mlx_init();
	scene_data->img.img_ptr = mlx_new_image(scene_data->mlx.mlx_ptr,
			WIDTH, HEIGHT);
	scene_data->img.data = (unsigned char*) mlx_get_data_addr(scene_data->img.img_ptr,
			&(scene_data->img.bits_per_pixel), &(scene_data->img.size_line),
			&(scene_data->img.endian));
	scene_data->mlx.win_ptr = mlx_new_window(scene_data->mlx.mlx_ptr,
			WIDTH, HEIGHT, "minirt");
}

void	init_scene_data(t_data *scene_data)
{
	t_shape	*shape;

	shape = NULL;
	scene_data->amb_set = 0;
	scene_data->wrld.shapes = ft_lstnew(shape);
}


void write_pixel1(unsigned char *dst, double w, double h, t_color color,t_data *scene_data)
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
    *(unsigned int*)dst  = color_code;
}


int	main(int argc, char **argv)	
{
	t_data	scene_data;
	t_camera2 c;
	t_point		from;
	t_point		to;
    t_vector	up;

	(void) argc;
	(void) argv;
  	if (argc != 2)
        print_error_msg_and_exit("NOT ENOUGH ARGUMENTS", &scene_data);    
	init_scene_data(&scene_data);
	parse_scene(argv[1], &scene_data);
	setup_mlx(&scene_data);

	scene_data.wrld.shapes = scene_data.wrld.shapes->next;
	default_world(&scene_data);
	c = camera(HEIGHT, WIDTH , 1.0471975512);

	from = point(0, 0, -5);
	to = point(0, 0, -1);
	up = vector(0, 1, 0);
	c.transform = view_transform(from, to, up);
	
	render(c, scene_data.wrld ,  &scene_data);
	mlx_put_image_to_window(scene_data.mlx.mlx_ptr, scene_data.mlx.win_ptr,
		scene_data.img.img_ptr, 0, 0);
	mlx_key_hook(scene_data.mlx.win_ptr, &key, &scene_data);
	mlx_loop(scene_data.mlx.mlx_ptr);
	return (0);
}