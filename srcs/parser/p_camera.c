#include "../../includes/minirt.h"

// int verify_digits(char **nrm_vec_split, char **pnt_split, char **info)
// {
//     int i;

//     i = 0;
//     while (i < 3)
//     {
//         if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]))
//             return (0);
//         i++;
//     }
//     if (skip_dot_verify_digits(info[3]))
//         return (0);
//     return(1);
// }

void store_in_scene_data(t_data *scene_data, char **point_split, char **norm_vec_split, char **info)
{
    scene_data->camera.pos.x = parse_double(point_split[0]);
    scene_data->camera.pos.y = parse_double(point_split[1]);
    scene_data->camera.pos.z = parse_double(point_split[2]);
    scene_data->camera.norm_vector.x = parse_double(norm_vec_split[0]);
    scene_data->camera.norm_vector.y = parse_double(norm_vec_split[1]);
    scene_data->camera.norm_vector.z = parse_double(norm_vec_split[2]);
    scene_data->camera.fov = parse_double(info[3]);
}

int parse_camera(char **info, t_data *scene_data, char **point_split, char **norm_split)
{
    double **transform;
    if (scene_data->num_objs.num_cam == 1)
        return (set_error_obj(1, "CAMERA IS ALREADY SET", scene_data));
    if (get_2darray_size(info) != 4)
        return (set_error_obj(1, "WRONG NUMBER OF ARGUMENTS IN CAMERA", scene_data));
    if(skip_dot_verify_digits(info[3]))
        return (set_error_obj(1, "CAMERA FOV IS NOT A NUMBER", scene_data));
    scene_data->camera.fov = parse_double(info[1]);
    if (scene_data->camera.fov < 0 || scene_data->amb_ratio > 180)
        return (set_error_obj(1, "CAMERA FOV SHOULD BE BETWEEN 0 AND 180", scene_data));
    if(comma_count(info[1]) != 2)
        return (set_error_obj(1, "CAMERA POINT FORMAT IS INCORRECT", scene_data));
    if(comma_count(info[2]) != 2)
        return (set_error_obj(1, "CAMERA VECTOR FORMAT IS INCORRECT", scene_data));
    point_split = ft_split(info[1], ',');
    norm_split = ft_split(info[2], ',');        
    if (get_2darray_size(point_split) != 3)
        return (set_error_obj(2, "CAMERA POINT SHOULD HAVE 3 VALUES",scene_data));
    if (get_2darray_size(norm_split) != 3)
        return (set_error_obj(2, "CAMERA NORM VECTOR SHOULD HAVE 3 VALUES",scene_data));
    if (!verify_digits(point_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CAMERA POINT VALUES",scene_data));  
    if (!verify_digits(norm_split))
        return (set_error_obj(2, "ONLY DIGITS ALLOWED IN CAMERA NORM VECTOR VALUES",scene_data));
        
    store_in_scene_data(scene_data, point_split, norm_split, info);

    t_point from ;
    t_point to;
    t_vector up;

    from = point(scene_data->camera.pos.x, scene_data->camera.pos.y, scene_data->camera.pos.z);
    t_tuple to_tp_point;
    t_tuple to_tp_vector;
    t_tuple to_result;

    to_tp_point = tuple(scene_data->camera.norm_vector.x, scene_data->camera.norm_vector.y, scene_data->camera.norm_vector.z ,1 );
    to_tp_vector = tuple(scene_data->camera.pos.x, scene_data->camera.pos.y, scene_data->camera.pos.z ,0);
    to_result = add(to_tp_point, to_tp_vector);
    to = point(to_result.x, to_result.y, to_result.z);
    
    t_vector up1_vec;
    up1_vec = cross(scene_data->camera.norm_vector, vector(0, 1, 1));

    up = cross(up1_vec , scene_data->camera.norm_vector);

    transform = view_transform(from , to , up);
    scene_data->camera2.transform = transform;
    scene_data->camera2 =  camera(WIDTH , HEIGHT, scene_data->camera.fov);
    t_tuple origin_tp;
    scene_data->camera2.transform = inverse(transform, 4);
    origin_tp =   matrix_multi_tp(scene_data->camera2.transform, tuple(0, 0, 0, 1));
    scene_data->camera2.origin = point(origin_tp.x, origin_tp.y, origin_tp.z);
    free_2d_array(transform, 4);
    scene_data->num_objs.num_cam += 1;
   

    if (scene_data->camera2.transform == NULL)
        return (set_error_obj(2, "CAMERA MATIX NOT INVERTIBLE",scene_data));
    scene_data->num_objs.num_cam += 1; 
    return(1);
}
