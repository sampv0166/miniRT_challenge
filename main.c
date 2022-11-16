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
	t_shape *shape;

	shape = NULL;
	scene_data->amb_set = 0;
	scene_data->wrld.shapes = ft_lstnew(shape);
}
void print_parsed_values(t_data *scene_data)
{
	printf("\nAMBIENCE RATIO\n");
    printf("%f\n", scene_data->amb_ratio);
	printf("\nAMBIENCE COLOR\n");
    printf("%f\n", scene_data->amb_color.r);
    printf("%f\n", scene_data->amb_color.g);
    printf("%f\n", scene_data->amb_color.b);
	printf("---------------------------------\n");
    printf("\nCAMERA LOCATION\n");
    printf("%f\n", scene_data->camera.pos.x);
    printf("%f\n",  scene_data->camera.pos.y);
    printf("%f\n",  scene_data->camera.pos.z);
    printf("\nCAMERA NORM VECTOR\n");
    printf("%f\n", scene_data->camera.norm_vector.x);
    printf("%f\n", scene_data->camera.norm_vector.y);
    printf("%f\n", scene_data->camera.norm_vector.z);
	printf("\nCAMERA FOV\n");
    printf("%f\n", scene_data->camera.fov);
	printf("---------------------------------");
    printf("\n LIGHT SOURCE POINT\n");
    printf("%f\n", scene_data->light_src.pos.x);
    printf("%f\n",  scene_data->light_src.pos.y);
    printf("%f\n",  scene_data->light_src.pos.z);
	printf("\nLight COLOR\n");
    printf("%f\n", scene_data->light_src.color.r);
     printf("%f\n", scene_data->light_src.color.r);
    printf("%f\n", scene_data->light_src.color.r);
	printf("\nLIGHT RATIO\n");
    printf("%f\n", scene_data->light_src.ratio);
	printf("---------------------------------");
	scene_data->wrld.shapes = scene_data->wrld.shapes->next;

    while (scene_data->wrld.shapes)
    {
		t_shape *shape;
		shape = (t_shape *) scene_data->wrld.shapes->content;

		if (!ft_strncmp(shape->shape_name, "sp", 2))
		{
			printf("here");
			printf("\n SPHERE CENTER POINT\n");
			printf("%s\n", shape->shape_name);
			printf("%f\n", shape->position.x);
			printf("%f\n",  shape->position.y);
			printf("%f\n",  shape->position.z);
				
			printf("\nsphere color\n");
			printf("%f\n", shape->color.r);
			printf("%f\n",  shape->color.g);
			printf("%f\n",  shape->color.b);
			printf("\nradiance\n");
			printf("%f\n", shape->radius);
		}
	
		if (!ft_strncmp(shape->shape_name, "pl", 2))
		{
			printf("\n plane point xyz\n");
			printf("%f\n", shape->position.x);
			printf("%f\n",  shape->position.y);
			printf("%f\n",  shape->position.z);
			printf("\n norm vec\n");
			printf("%f\n", shape->norm_vector.x);
			printf("%f\n",  shape->norm_vector.y);
			printf("%f\n",  shape->norm_vector.z);
			printf("\nplane color\n");
			printf("%f\n", shape->color.r);
			printf("%f\n",  shape->color.g);
			printf("%f\n",  shape->color.b);
		}
		if (!ft_strncmp(shape->shape_name, "cy", 2))
		{
			printf("\n cy point xyz\n");
			printf("%f\n", shape->position.x);
			printf("%f\n",  shape->position.y);
			printf("%f\n",  shape->position.z);
			printf("\n norm vec\n");
			printf("%f\n", shape->norm_vector.x);
			printf("%f\n",  shape->norm_vector.y);
			printf("%f\n",  shape->norm_vector.z);
			printf("\ncy color\n");
			printf("%f\n", shape->color.r);
			printf("%f\n",  shape->color.g);
			printf("%f\n",  shape->color.b);
			printf("\ncy diameter\n");
			printf("%f\n", shape->diameter);
			printf("\ncy height\n");
			printf("%f\n", shape->height);
		}
		printf("---------------------------------");
				
		scene_data->wrld.shapes = scene_data->wrld.shapes->next;
    }
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
	default_world(&scene_data);
	setup_mlx(&scene_data);
	c = camera(HEIGHT, WIDTH , (scene_data.camera.fov * (PI/180)));
	from = scene_data.camera.pos;
	to = point(0,3,-7);
    up = scene_data.camera.norm_vector;
    c.transform = view_transform(from, to, up);
    c.transform = inverse(c.transform, 4);
	// print_parsed_values(&scene_data);
	// exit(0);
	// t_shape *ss;
	// ss = (t_shape *) scene_data.wrld.shapes->content;
	// 
	// printf("%s" , ss->shape_name);
	scene_data.wrld.shapes = scene_data.wrld.shapes->next;
	render(c, scene_data.wrld, &scene_data);
	
	mlx_put_image_to_window(scene_data.mlx.mlx_ptr, scene_data.mlx.win_ptr,
		scene_data.img.img_ptr, 0, 0);
	mlx_key_hook(scene_data.mlx.win_ptr, &key, &scene_data);
	mlx_loop(scene_data.mlx.mlx_ptr);
	return (0);
}