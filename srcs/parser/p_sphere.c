#include "../../includes/minirt.h"

static int verify_digits( char **pnt_split, char **color_split ,char **info)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[2]))
        return (0); 
    return(1);
}

// !REDUCE TO 25 LINES  - SAMAD
void parse_sphere(char **info, t_data *scene_data)
{
    char **point_split;
    char **color_split;
    t_shape *sphere;

    if (get_2darray_size(info) != 4)
        print_error_msg_and_exit("INVALID NUMBER OF VALUES FOR SPHERE", scene_data);
    
    point_split = ft_split(info[1], ',');
    color_split = ft_split(info[3], ',');
    if (get_2darray_size(point_split) == 3 && get_2darray_size(color_split) == 3
        && verify_digits(point_split ,color_split, info) )
    {
        sphere = malloc (sizeof (t_shape));

        sphere->position.x = parse_double(point_split[0]);
        sphere->position.y = parse_double(point_split[1]);
        sphere->position.z = parse_double(point_split[2]);
        
        sphere->radius = parse_double(info[2]);

        parse_color(info[3], scene_data, &sphere->color);
        // sphere->transform = identity_matrix();
        sphere->material.shininess = 200.0;;
	    sphere->material.diffuse = 0.7;
		sphere->material.specular = 0.2;

		sphere->material.color.r = sphere->color.r/ 255;
		sphere->material.color.g = sphere->color.g/ 255;
		sphere->material.color.b = sphere->color.b/ 255;

        sphere->shape_name = "sp";
        sphere->material.ambient = scene_data->amb_ratio;



    double **	scale;
	double **	transform;
	double **	translate;


	translate = translation(tuple (sphere->position.x,sphere->position.y, sphere->position.z, 1));
	scale = scaling(tuple (sphere->radius/ 2, sphere->radius/ 2, sphere->radius / 2, 1));
	transform = matrix_multi(scale, translate);
	sphere->transform = transform;
	free_2d_array(translate, 4);
	free_2d_array(scale, 4);
    // print_matrix(sphere->transform, 4);
    // exit(0);
		// double **scale;
        // double **translated;


		// translated = translation(tuple(sphere->position.x, sphere->position.y , sphere->position.z , 1));
        // scale = scaling(tuple(sphere->radius / 2, sphere->radius / 2,sphere->radius / 2, 1));
        // sphere->transform =  matrix_multi(translated, scale);



		// sphere->transform = identity_matrix();
        // transalation
        // scaling
        // rotation
        // skew

        ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(sphere));
    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(color_split);
                 free(point_split);
     free(color_split);
        print_error_msg_and_exit("Wrong Input", scene_data);  
    }
    free_2d_char_array(point_split);
    free_2d_char_array(color_split);
             free(point_split);
     free(color_split);
}