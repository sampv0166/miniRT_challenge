#include "../includes/minirt.h"


void print_vector(t_vector vector)
{
		printf("\n%f,",vector.x);
	printf("%f,", vector.y);
	printf("%f\n", vector.z);
}

void print_point(t_point point)
{
		printf("%f\n",point.x);
	printf("%f\n", point.y);
	printf("%f\n", point.z);
}

void	print_parsed_values(t_data *scene_data)
{
	t_shape	*shape;

	printf("\nAMBIENCE RATIO\n");
	printf("%f\n", scene_data->amb_ratio);
	printf("\nAMBIENCE COLOR\n");
	printf("%f\n", scene_data->amb_color.r);
	printf("%f\n", scene_data->amb_color.g);
	printf("%f\n", scene_data->amb_color.b);
	printf("---------------------------------\n");
	printf("\nCAMERA LOCATION\n");
	printf("%f\n", scene_data->camera.pos.x);
	printf("%f\n", scene_data->camera.pos.y);
	printf("%f\n", scene_data->camera.pos.z);
	printf("\nCAMERA NORM VECTOR\n");
	printf("%f\n", scene_data->camera.norm_vector.x);
	printf("%f\n", scene_data->camera.norm_vector.y);
	printf("%f\n", scene_data->camera.norm_vector.z);
	printf("\nCAMERA FOV\n");
	printf("%f\n", scene_data->camera.fov);
	printf("---------------------------------");
	printf("\n LIGHT SOURCE POINT\n");
	printf("%f\n", scene_data->light_src.pos.x);
	printf("%f\n", scene_data->light_src.pos.y);
	printf("%f\n", scene_data->light_src.pos.z);
	printf("\nLight COLOR\n");
	printf("%f\n", scene_data->light_src.color.r);
	printf("%f\n", scene_data->light_src.color.g);
	printf("%f\n", scene_data->light_src.color.b);
	printf("\nLIGHT RATIO\n");
	printf("%f\n", scene_data->light_src.ratio);
	printf("---------------------------------");
	scene_data->wrld.shapes = scene_data->wrld.shapes->next;

	while (scene_data->wrld.shapes)
	{
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
			printf("%f\n", shape->norm_vector.y);
			printf("%f\n", shape->norm_vector.z);
			printf("\nplane color\n");
			printf("%f\n", shape->color.r);
			printf("%f\n", shape->color.g);
			printf("%f\n", shape->color.b);
		}
		if (!ft_strncmp(shape->shape_name, "cy", 2))
		{
			printf("\n cy point xyz\n");
			printf("%f\n", shape->position.x);
			printf("%f\n", shape->position.y);
			printf("%f\n", shape->position.z);
			printf("\n norm vec\n");
			printf("%f\n", shape->norm_vector.x);
			printf("%f\n", shape->norm_vector.y);
			printf("%f\n", shape->norm_vector.z);
			printf("\ncy color\n");
			printf("%f\n", shape->color.r);
			printf("%f\n", shape->color.g);
			printf("%f\n", shape->color.b);
			printf("\ncy diameter\n");
			printf("%f\n", shape->diameter);
			printf("\ncy height\n");
			printf("%f\n", shape->height);
		}
		printf("---------------------------------");
		scene_data->wrld.shapes = scene_data->wrld.shapes->next;
	}
}



void	print_matrix(double **mat, int col)
{
	int		i;
	int		j;

	i = 0;
	if (!mat)
		return ;
	while (i < col)
	{
		j = 0;
		while (j < col)
		{
			printf("| %lf\t", mat[i][j]);
			j++;
		}
		printf("|\n");
		i++;
	}
}
