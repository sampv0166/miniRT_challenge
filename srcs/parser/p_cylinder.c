#include "../../includes/minirt.h"

static void store_in_scene_data(t_data *scene_data, char **point_split, char **norm_vec, char **info)
{
    t_shape *cy;
    cy = malloc (sizeof (t_shape));
    cy->position.x = parse_double(point_split[0]);
    cy->position.y = parse_double(point_split[1]);
    cy->position.z = parse_double(point_split[2]);
    
    cy->norm_vector.x = parse_double(norm_vec[0]);
    cy->norm_vector.y = parse_double(norm_vec[1]);
    cy->norm_vector.z = parse_double(norm_vec[2]);

    parse_color(info[5], scene_data, &cy->color);
    cy->diameter = parse_double(info[3]);
    cy->height = parse_double(info[4]);
    cy->transform = identity_matrix();
    cy->material.shininess = 200.0;
    cy->material.diffuse = 0.7;
    cy->material.specular = 0.2;
    cy->shape_name = "cy";
    cy->material.ambient = scene_data->amb_ratio;
	cy->material.color.r = cy->color.r/ 255;
	cy->material.color.g = cy->color.g/ 255;
	cy->material.color.b = cy->color.b/ 255;

    // cy->transform = translation(tuple (cy->position.x,cy->position.y,cy->position.z,1));
    
    	double**	translate;
	double**	rotate;
	double**	scale;
	double**	transform;
	double		radius;

	radius = cy->diameter * 0.5;
	scale = scaling(tuple (radius, cy->height * 0.5, radius, 1));
	translate = translation(tuple (cy->position.x,
		cy->position.y, cy->position.z, 1));
	transform = matrix_multi(translate, scale);
	// free_matrix(translate);
	rotate = normal_rotation_matrix(tuple(cy->norm_vector.x, cy->norm_vector.y, cy->norm_vector.z ,0 ));
	translate = matrix_multi(rotate, transform);
	cy->transform = translate;
	// free_matrix(rotate);
	// free_matrix(transform);
	// free_matrix(scale);
    
    
    // transalation
    // scaling
    // rotation
    // skew
    // spehere.transform = transformed matrix
    ft_lstadd_back(&scene_data->wrld.shapes,ft_lstnew(cy) );
}

static int verify_digits(char **nrm_vec_split, char **pnt_split, char **color_split ,char **info)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[3]) || skip_dot_verify_digits(info[4]))
        return(0);    
    return(1);
}

void parse_cylinder(char **info, t_data *scene_data)
{
    char **point_split;
    char **color_split;
    char **norm_vec;

    if (get_2darray_size(info) != 6)
    {
        print_error_msg_and_exit("invalid input", scene_data);
    }
    point_split = ft_split(info[1], ',');
    norm_vec = ft_split(info[2], ',');
    color_split = ft_split(info[5], ',');
    
    if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec) == 3 && 
        get_2darray_size(color_split) == 3 &&  verify_digits(norm_vec, point_split ,color_split, info))
    {
        store_in_scene_data(scene_data, point_split, norm_vec, info);
    }
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(norm_vec);
        free_2d_char_array(color_split);
        print_error_msg_and_exit("Wrong Input", scene_data);
    }
    free_2d_char_array(point_split);
    free_2d_char_array(norm_vec);
    free_2d_char_array(color_split);
}