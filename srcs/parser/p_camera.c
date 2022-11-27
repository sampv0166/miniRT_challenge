#include "../../includes/minirt.h"

int verify_digits(char **nrm_vec_split, char **pnt_split, char **info)
{
    int i;

    i = 0;
    while (i < 3)
    {
        if (skip_dot_verify_digits(nrm_vec_split[i]) || skip_dot_verify_digits(pnt_split[i]))
            return (0);
        i++;
    }
    if (skip_dot_verify_digits(info[3]))
        return (0);
    return(1);
}

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

void parse_camera(char **info, t_data *scene_data)
{
    char **point_split;
    char **norm_vec_split;
    double **transform;

    if (get_2darray_size(info) != 4)
    {
        print_error_msg_and_exit("Wrong Input", scene_data);  
    }
    point_split = ft_split(info[1], ',');
    norm_vec_split = ft_split(info[2], ',');
    if (get_2darray_size(point_split) == 3 && get_2darray_size(norm_vec_split) == 3 &&
        verify_digits(norm_vec_split, point_split , info))
    {        
        store_in_scene_data(scene_data, point_split, norm_vec_split, info);

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

        // print_tuple_sam(&to_result);
        // exit(0);
        to = point(to_result.x, to_result.y, to_result.z);
        
        t_vector up1_vec;
        // t_vector up2_vec;

        up1_vec = cross(scene_data->camera.norm_vector, vector(0, 1, 1));

        up = cross(up1_vec , scene_data->camera.norm_vector);

        // print_point(from);

        // print_point(to);

        // print_vector(up);

        // exit(0);

        transform = view_transform(from , to , up);
        scene_data->camera2.transform = transform;
		// rt->cam->transform = invert_matrix(transform);

        // scene_data->camera2.transform = inverse(transform, 4);
       
        // print_matrix(scene_data->camera2.transform, 4);
        
		scene_data->camera2 =  camera(WIDTH , HEIGHT, scene_data->camera.fov);
        t_tuple origin_tp;
        scene_data->camera2.transform = inverse(transform, 4);
        origin_tp =   matrix_multi_tp(scene_data->camera2.transform, tuple(0, 0, 0, 1));
		scene_data->camera2.origin = point(origin_tp.x, origin_tp.y, origin_tp.z);
         free_2d_array(transform, 4);
        
        //  print_point(point(origin_tp));
        //  printf("%f, %f, %f", origin_tp.x, origin_tp.y, origin_tp.z);
        //  exit(0);
    }   
    else
    {
        free_2d_char_array(point_split);
        free_2d_char_array(norm_vec_split);
        free(point_split);
        free(norm_vec_split);
        print_error_msg_and_exit("Wrong Input", scene_data);
    }
    free_2d_char_array(point_split);
    free_2d_char_array(norm_vec_split);
    free(point_split);
     free(norm_vec_split);
}
