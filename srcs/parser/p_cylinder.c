#include "../../includes/minirt.h"

int store_in_scene_data_cy(t_data *scene_data, char **point_split, char **norm_vec, char **info, t_color *color)
{
    t_shape *cy;

    if (!parse_color(info[5] , color))
        return (set_error_obj(2, "CYLINDER COLOR VALUE IS WRONG",scene_data));

    cy = malloc (sizeof (t_shape));
    cy->position.x = parse_double(point_split[0]);
    cy->position.y = parse_double(point_split[1]);
    cy->position.z = parse_double(point_split[2]);
    
    cy->norm_vector.x = parse_double(norm_vec[0]);
    cy->norm_vector.y = parse_double(norm_vec[1]);
    cy->norm_vector.z = parse_double(norm_vec[2]);
    // parse_color(info[5], &cy->color);
    cy->color.r = color->r;
    cy->color.g = color->g;
    cy->color.b = color->b;

    cy->diameter = parse_double(info[3]);
    cy->height = parse_double(info[4]);
    // cy->transform = identity_matrix();
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
	free_2d_array(translate, 4);
	rotate = normal_rotation_matrix(tuple(cy->norm_vector.x, cy->norm_vector.y, cy->norm_vector.z ,0 ));
	translate = matrix_multi(rotate, transform);
	cy->transform = translate;
	cy->inverse =  inverse(translate  , 4);
	free_2d_array(rotate, 4);
	free_2d_array(transform, 4);
	free_2d_array(scale, 4);
    // transalation
    // scaling
    // rotation
    // skew
    // spehere.transform = transformed matrix
    ft_lstadd_back(&scene_data->wrld.shapes,ft_lstnew(cy) );


    if (cy->inverse == NULL)
        return (set_error_obj(2, "CYLINDER MATRIX IS NOT INVERTIBLE",scene_data));  

    return (1);
}

// static int verify_digits(char **nrm_vec_split, char **pnt_split, char **color_split ,char **info)
// {
//     int i;

//     i = 0;
//     while (i < 3)
//     {
//         if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
//             return (0);
//         i++;
//     }
//     if (skip_dot_verify_digits(info[3]) || skip_dot_verify_digits(info[4]))
//         return(0);    
//     return(1);
// }

int parse_cylinder(char **info, t_data *scene_data, char **point_split,char** color_split,char** norm_split)
{
    t_color color;

     if (get_2darray_size(info) != 6)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CYLINDER", scene_data));
    if(comma_count(info[1]) != 2)
        return (set_error_obj(1, "CYLINDER POINT FORMAT IS INCORRECT", scene_data));
    if(comma_count(info[5]) != 2)
        return (set_error_obj(1, "CYLINDER COLOR FORMAT IS INCORRECT", scene_data));
    if(comma_count(info[2]) != 2)
        return (set_error_obj(1, "CYLINDER NORM VEC FORMAT IS INCORRECT", scene_data));     
    if (skip_dot_verify_digits(info[3]))
         return (set_error_obj(1, "DIAMETER OF CYLINDER SHOULD BE A NUMBER", scene_data));
    if (skip_dot_verify_digits(info[3]))
         return (set_error_obj(1, "HEIGHT OF CYLINDER SHOULD BE A NUMBER", scene_data));
    point_split = ft_split(info[1], ',');
    color_split = ft_split(info[5], ',');
    norm_split = ft_split(info[2], ',');
    if (get_2darray_size(point_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CYLINDER POINT", scene_data));
    if (get_2darray_size(color_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CYLINDER  COLOR", scene_data));
    if (get_2darray_size(norm_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CYLINDER NORM VECTOR", scene_data));
    if (!verify_digits(point_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CYLINDER POINT VALUES",scene_data)); 
    if (!verify_digits(color_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CYLINDER COLOR VALUES",scene_data));
    if (!verify_digits(norm_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CYLINDER NORM VECTOR VALUES",scene_data));     
    if (!parse_color(info[5], &color))
        return (set_error_obj(2, "CYLINDER COLOR VALUE IS WRONG",scene_data));
    if (!store_in_scene_data_cy(scene_data, point_split, norm_split, info , &color))
        return(0);
    // char **point_split;
    // char **color_split;
    // char **norm_vec;

    // if (get_2darray_size(info) != 6)
    //     return (0);
    // point_split = ft_split(info[1], ',');
    // norm_vec = ft_split(info[2], ',');
    // color_split = ft_split(info[5], ',');
    
    // if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec) == 3 && 
    //     get_2darray_size(color_split) == 3 &&  verify_digits(norm_vec, point_split ,color_split, info))
    // {
    //     if(!store_in_scene_data_cy(scene_data, point_split, norm_vec, info))
    //         return (0);
    // }
    // else
    // {
    //     free_2d_char_array(point_split);
    //     free_2d_char_array(norm_vec);
    //     free_2d_char_array(color_split);
    //                          free(point_split);
    //  free(color_split);
    //    free(norm_vec);
    //     return(0);
    // }
    // free_2d_char_array(point_split);
    // free_2d_char_array(norm_vec);
    // free_2d_char_array(color_split);
    //                      free(point_split);
    //  free(color_split);
    //    free(norm_vec);
    scene_data->num_objs.num_cy += 1;
    return (1);
}