#include "../../includes/minirt.h"

// static int verify_digits(char **nrm_vec_split, char **pnt_split, char **color_split )
// {
//     int i;

//     i = 0;
//     while (i < 3)
//     {
//         if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]) || skip_dot_verify_digits(color_split[i]) )
//             return (0);
//         i++;
//     }  
//     return(1);
// }

double  **normal_rotation_matrix(t_tuple normal)
{
	double		angle;
	double		vals[3];
	t_vector	axis;
	double	    **rotation;
    
	rotation = identity_matrix();
    angle = acos(dot(normal, tuple(0, 1, 0, 0)));
	axis = cross(vector(normal.x, normal.y, normal.z), vector(0, 1, 0));
	vals[0] = cos(angle);
	vals[1] = sin(angle);
	vals[2] = 1.0 - vals[0];
	rotation[0][0] = vals[0] + (pow(axis.x, 2) * vals[2]);
	rotation[0][1] = (axis.x * axis.y * vals[2]) - (axis.z * vals[1]);
	rotation[0][2] = (axis.x * axis.z * vals[2]) + (axis.y * vals[1]);
	rotation[1][0] = (axis.y * axis.z * vals[2]) + (axis.z * vals[1]);
	rotation[1][1] = vals[0] + (pow(axis.y, 2) * vals[2]);
	rotation[1][2] = (axis.y * axis.z * vals[2]) - (axis.x * vals[1]);
	rotation[2][0] = (axis.z * axis.x * vals[2]) - (axis.y * vals[1]);
	rotation[2][1] = (axis.z * axis.y * vals[2]) + (axis.x * vals[1]);
	rotation[2][2] = vals[0] + (pow(axis.z, 2) * vals[2]);
	rotation[3][3] = 1;
	return (rotation);
}


int store_in_scene_data_plane(t_data *scene_data, char **point_split, char **norm_vec, char **info, t_color *color)
{
    t_shape *plane;


    if (!parse_color(info[3], color))
        return (set_error_obj(2, "PLANE COLOR VALUE IS WRONG",scene_data));    
    

    plane =  malloc (sizeof (t_shape));
    plane->position.x = parse_double(point_split[0]);
    plane->position.y = parse_double(point_split[1]);
    plane->position.z = parse_double(point_split[2]);

    plane->norm_vector.x = parse_double(norm_vec[0]);
    plane->norm_vector.y = parse_double(norm_vec[1]);
    plane->norm_vector.z = parse_double(norm_vec[2]);

    plane->color.r = color->r;
    plane->color.g = color->g;
    plane->color.b = color->b;
    
    plane->material.shininess = 200.0;;
    plane->material.diffuse = 0.7;
    plane->material.specular = 0.2;
    plane->shape_name = "pl";
    plane->material.ambient = scene_data->amb_ratio;
	plane->material.color.r = plane->color.r/ 255;
	plane->material.color.g = plane->color.g/ 255;
	plane->material.color.b = plane->color.b/ 255;


    double**	translate;
	double**	rotate;
	double**	transform;
  
	translate = translation(tuple (plane->position.x,
		plane->position.y, plane->position.z, 1));
    rotate = normal_rotation_matrix(tuple(plane->norm_vector.x , plane->norm_vector.y, plane->norm_vector.z, 0));
    transform = matrix_multi(translate , rotate);
    plane->transform = transform ;
	plane->inverse = inverse(plane->transform  , 4);
    free_2d_array(translate, 4);
    free_2d_array(rotate , 4);

    ft_lstadd_back(&scene_data->wrld.shapes, ft_lstnew(plane));

    if (plane->inverse == NULL)
        return (set_error_obj(2, "PLANE MATRIX IS NOT INVERTIBLE",scene_data));  

    return (1);
}

int parse_plane(char **info, t_data *scene_data, char **point_split,char** color_split,char** norm_split)
{
    t_color color;

     if (get_2darray_size(info) != 4)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE", scene_data));
    if(comma_count(info[1]) != 2)
        return (set_error_obj(1, "PLANE POINT FORMAT IS INCORRECT", scene_data));
    if(comma_count(info[3]) != 2)
        return (set_error_obj(1, "PLANE COLOR FORMAT IS INCORRECT", scene_data));
    if(comma_count(info[2]) != 2)
        return (set_error_obj(1, "PLANE NORM VEC FORMAT IS INCORRECT", scene_data));     
    point_split = ft_split(info[1], ',');
    color_split = ft_split(info[3], ',');
    norm_split = ft_split(info[2], ',');
    if (get_2darray_size(point_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE POINT", scene_data));
    if (get_2darray_size(color_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE  COLOR", scene_data));
    if (get_2darray_size(norm_split) != 3)
         return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN PLANE NORM VECTOR", scene_data));
   
    if (!verify_digits(point_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN PLANE POINT VALUES",scene_data)); 
    if (!verify_digits(color_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN PLANE COLOR VALUES",scene_data));
    if (!verify_digits(norm_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN PLANE NORM VECTOR VALUES",scene_data));     
    if (!parse_color(info[3], &color))
        return (set_error_obj(2, "PLANE COLOR VALUE IS WRONG",scene_data));
    if (!store_in_scene_data_plane(scene_data, point_split, norm_split, info , &color))
        return(0);




    // if (get_2darray_size(info) != 4)
    //     return (0);
    // point_split = ft_split(info[1], ',');
    // norm_vec = ft_split(info[2], ',');
    // color_split = ft_split(info[3], ',');
    // if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec) == 3 &&
    //     get_2darray_size(color_split) == 3 && verify_digits(norm_vec,point_split,color_split) )
    // {
    //     if (!store_in_scene_data_plane(scene_data, point_split, norm_vec, info))
    //         return(0);
    // }
    // else
    // {
    //     free_2d_char_array(point_split);
    //     free_2d_char_array(norm_vec);
    //     free_2d_char_array(color_split);
    //     free(point_split);
    //     free(color_split);
    //     free(norm_vec);
    //     return (0); 
    // }
    // free_2d_char_array(point_split);
    // free_2d_char_array(norm_vec);
    // free_2d_char_array(color_split);
    //                  free(point_split);
    //  free(color_split);
    //    free(norm_vec);
    scene_data->num_objs.num_pl += 1;
     return (1);  
}