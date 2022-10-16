#include "./includes/minirt.h"

#include "./includes/utils.h"

#include "./includes/parse.h"

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
		printf("here");
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


void init_scene_data (t_data *scene_data)
{
	scene_data->amb_set = 0;
}

int	main(int argc, char **argv)	
{
	t_data	scene_data;

	(void) argc;
	(void) argv;
  	if (argc != 2)
        print_error_msg_and_exit("NOT ENOUGH ARGUMENTS", &scene_data);    
	init_scene_data(&scene_data);
	parse_scene(argv[1], &scene_data);
	

	setup_mlx(&scene_data);
	mlx_put_image_to_window(scene_data.mlx.mlx_ptr, scene_data.mlx.win_ptr,
		scene_data.img.img_ptr, 0, 0);
	mlx_key_hook(scene_data.mlx.win_ptr, &key, &scene_data);
	mlx_loop(scene_data.mlx.mlx_ptr);
	
	return (0);
}
